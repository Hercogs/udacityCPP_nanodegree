#ifndef PROCESS_H
#define PROCESS_H

#include <string>
/*
Basic class for Process representation
It contains relevant attributes as shown below
*/
class Process {
 public:
  Process(int pid);
  int Pid();
  void CalculateCpu();
  std::string User();
  std::string Command();
  float CpuUtilization();
  std::string Ram();
  long int UpTime();
  bool operator<(Process const& a) const;

  // Declare any necessary private members
 private:
  int pid_;
  int ram_;

  long last_active_jiffies{0};
  long last_seconds{0};
  float cpu_util_{0.0};
};

#endif