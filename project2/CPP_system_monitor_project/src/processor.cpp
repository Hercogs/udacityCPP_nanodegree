#include "processor.h"

#include "linux_parser.h"

// Return the aggregate CPU utilization
float Processor::Utilization() {
  long current_active_jiffies = LinuxParser::ActiveJiffies();
  long current_total_jiffies = LinuxParser::Jiffies();

  float result =
      static_cast<float>(current_active_jiffies - last_active_jiffies) /
      (current_total_jiffies - last_total_jiffies);

  last_active_jiffies = current_active_jiffies;
  last_total_jiffies = current_total_jiffies;
  return result;
}