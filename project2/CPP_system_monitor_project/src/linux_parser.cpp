#include "linux_parser.h"

#include <dirent.h>
#include <unistd.h>

#include <string>
#include <vector>

using std::stof;
using std::string;
using std::to_string;
using std::vector;

// DONE: An example of how to read data from the filesystem
string LinuxParser::OperatingSystem() {
  string line;
  string key;
  string value;
  std::ifstream filestream(kOSPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "PRETTY_NAME") {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
      }
    }
  }
  return value;
}

// DONE: An example of how to read data from the filesystem
string LinuxParser::Kernel() {
  string os, version, kernel;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> version >> kernel;
  }
  return kernel;
}

// BONUS: Update this to use std::filesystem
vector<int> LinuxParser::Pids() {
  vector<int> pids;
  DIR* directory = opendir(kProcDirectory.c_str());
  struct dirent* file;
  while ((file = readdir(directory)) != nullptr) {
    // Is this a directory?
    if (file->d_type == DT_DIR) {
      // Is every character of the name a digit?
      string filename(file->d_name);
      if (std::all_of(filename.begin(), filename.end(), isdigit)) {
        int pid = stoi(filename);
        pids.push_back(pid);
      }
    }
  }
  closedir(directory);
  return pids;
}

// Read and return the system memory utilization
float LinuxParser::MemoryUtilization() {
  string mem_type;
  int mem_value, mem_total, mem_free;
  string line;
  std::ifstream stream(kProcDirectory + kMeminfoFilename);
  if (stream.is_open()) {
    while (std::getline(stream, line)) {
      std::istringstream linestream(line);
      linestream >> mem_type >> mem_value;
      if (mem_type == "MemTotal:") {
        mem_total = mem_value;
      }
      if (mem_type == "MemFree:") {
        mem_free = mem_value;
      }
    }
  }
  return (1. - static_cast<float>(mem_free) / mem_total);
}

// Read and return the system uptime
long int LinuxParser::UpTime() {
  string line;
  double uptime, idle_time;

  std::ifstream stream(kProcDirectory + kUptimeFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> uptime >> idle_time;
  }
  // printf("Uptime: %ld\n", static_cast<long>(uptime));
  return static_cast<long int>(uptime);
}

// Read and return the number of jiffies for the system
long LinuxParser::Jiffies() {
  return LinuxParser::ActiveJiffies() + LinuxParser::IdleJiffies();
}

// Read and return the number of active jiffies for a PID
long LinuxParser::ActiveJiffies(int pid) {
  long pid_jiffies{0};

  std::ifstream stream(kProcDirectory + std::to_string(pid) + kStatFilename);
  string line, name;
  string utime, stime, cutime, cstime;
  const int utime_idx = 13, stime_idx = 14, cutime_idx = 15, cstime_idx = 16;

  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);

    // Get specifix word from line
    int i = 0;  // Counter

    while (std::getline(linestream, name, ' ')) {
      if (i == utime_idx) {
        utime = name;
      }
      if (i == stime_idx) {
        stime = name;
      }
      if (i == cutime_idx) {
        cutime = name;
      }
      if (i == cstime_idx) {
        cstime = name;
      }
      ++i;
    }

    try {
      pid_jiffies = std::stol(utime) + std::stol(stime) + std::stol(cutime) +
                    std::stol(cstime);
      pid_jiffies = std::stol(utime) + std::stol(stime);
    } catch (...) {
      pid_jiffies = 0;
    }
  }

  return pid_jiffies;
}

// Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() {
  vector<string> cpu = LinuxParser::CpuUtilization();
  long active = std::stol(cpu[LinuxParser::CPUStates::kUser_]) +
                std::stol(cpu[LinuxParser::CPUStates::kNice_]) +
                std::stol(cpu[LinuxParser::CPUStates::kSystem_]) +
                std::stol(cpu[LinuxParser::CPUStates::kIRQ_]) +
                std::stol(cpu[LinuxParser::CPUStates::kSoftIRQ_]) +
                std::stol(cpu[LinuxParser::CPUStates::kSteal_]);
  return active;
}

// Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() {
  vector<string> cpu = LinuxParser::CpuUtilization();
  long idle = std::stol(cpu[LinuxParser::CPUStates::kIdle_]) +
              std::stol(cpu[LinuxParser::CPUStates::kIOwait_]);
  return idle;
}

// Read and return CPU utilization
vector<string> LinuxParser::CpuUtilization() {
  string line, word;
  vector<string> out;

  std::ifstream stream(kProcDirectory + kStatFilename);
  if (stream.is_open()) {
    std::getline(stream, line);  // Get only first line
    std::istringstream linestream(line);
    while (linestream >> word) {
      out.push_back(word);
    }
    // Remove first element
    out.erase(out.begin());
  }
  return out;
}

// Read and return the total number of processes
int LinuxParser::TotalProcesses() {
  string line;

  string stat_name;
  int stat_value;
  std::ifstream stream(kProcDirectory + kStatFilename);
  while (std::getline(stream, line)) {
    std::stringstream linestream(line);
    linestream >> stat_name >> stat_value;
    if (stat_name == "processes") return stat_value;
  }
  return 0;
}

// Read and return the number of running processes
int LinuxParser::RunningProcesses() {
  string line;

  string stat_name;
  int stat_value;
  std::ifstream stream(kProcDirectory + kStatFilename);
  while (std::getline(stream, line)) {
    std::stringstream linestream(line);
    linestream >> stat_name >> stat_value;
    if (stat_name == "procs_running") return stat_value;
  }
  return 0;
}

// Read and return the command associated with a process
string LinuxParser::Command(int pid) {
  std::ifstream stream(kProcDirectory + std::to_string(pid) + kCmdlineFilename);

  string line, word;

  if (stream.is_open()) {
    std::getline(stream, line);  // Get only first line
    std::istringstream linestream(line);
    linestream >> word;
  }
  return word;
}

// Read and return the memory used by a process
string LinuxParser::Ram(int pid) {
  std::ifstream stream(kProcDirectory + std::to_string(pid) + kStatusFilename);

  string line, name;
  int ram_mb{0};
  while (std::getline(stream, line)) {
    std::istringstream linestream(line);
    linestream >> name;
    if (name == "VmSize:") {
      linestream >> ram_mb;
      break;
    }
  }
  ram_mb /= 1024;

  return std::to_string(ram_mb);
}

// Read and return the user ID associated with a process
string LinuxParser::Uid(int pid) {
  std::ifstream stream(kProcDirectory + std::to_string(pid) + kStatusFilename);

  string line, name;
  int uid{0};
  while (std::getline(stream, line)) {
    std::istringstream linestream(line);
    linestream >> name;
    if (name == "Uid:") {
      linestream >> uid;
      break;
    }
  }

  return std::to_string(uid);
}

// Read and return the user associated with a process
string LinuxParser::User(int pid) {
  string uid = LinuxParser::Uid(pid);

  std::ifstream stream(kPasswordPath);

  std::string line, word;

  while (std::getline(stream, line)) {
    std::istringstream linestream(line);

    std::string user, user_id;
    int i = 0;
    while (std::getline(linestream, word, ':')) {
      if (i == 0) {
        user = word;
      }
      if (i == 2) {
        user_id = word;
      }
      ++i;
    }

    if (uid == user_id) {
      return user;
    }
  }

  return "";
}

// Read and return the uptime of a process
long LinuxParser::UpTime(int pid) {
  std::ifstream stream(kProcDirectory + std::to_string(pid) + kStatFilename);

  string line, name;
  long UpTime;

  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);

    // Get specifix word from line
    const int word_idx = 21;
    int i = 0;  // Counter

    while (std::getline(linestream, name, ' ')) {
      if (i == word_idx) {
        UpTime = std::stol(name) / sysconf(_SC_CLK_TCK);
        break;
      }
      ++i;
    }
  }

  return UpTime;
}
