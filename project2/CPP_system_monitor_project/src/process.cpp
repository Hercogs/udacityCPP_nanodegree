#include "process.h"

#include <unistd.h>

#include <cctype>
#include <sstream>
#include <string>
#include <vector>

#include "linux_parser.h"

using std::string;
using std::to_string;
using std::vector;

// Constructor
Process::Process(int pid) { pid_ = pid; }

// Return this process's ID
int Process::Pid() { return pid_; }

void Process::CalculateCpu() {
  long current_active_jiffies = LinuxParser::ActiveJiffies(pid_);
  long uptime = LinuxParser::UpTime();

  long seconds = uptime - LinuxParser::UpTime(pid_);

  // Calculate average cpu usage
  cpu_util_ =
      ((current_active_jiffies - last_active_jiffies) / sysconf(_SC_CLK_TCK)) /
      static_cast<float>(seconds - last_seconds);

  last_active_jiffies = current_active_jiffies;
  last_seconds = seconds;
}

// Return this process's CPU utilization
float Process::CpuUtilization() { return cpu_util_; }

// Return the command that generated this process
string Process::Command() { return LinuxParser::Command(pid_); }

// Return this process's memory utilization
string Process::Ram() {
  string ram_string = LinuxParser::Ram(pid_);
  ram_ = std::stoi(ram_string);
  return ram_string;
}

// Return the user (name) that generated this process
string Process::User() { return LinuxParser::User(pid_); }

// Return the age of this process (in seconds)
long int Process::UpTime() {
  return LinuxParser::UpTime() - LinuxParser::UpTime(pid_);
}

// Overload the "less than" comparison operator for Process objects
bool Process::operator<(Process const& a) const {
  // if (std::stoi(this.pid_) < std::stoi("12")){
  if (cpu_util_ < a.cpu_util_) {
    return true;
  } else {
    return false;
  }
}