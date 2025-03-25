#include "process.h"

#include <unistd.h>

#include <cctype>
#include <string>

#include "linux_parser.h"

using std::string;
using std::vector;

Process::Process(int pid)
    : pid_(pid),
      process_stats_(LinuxParser::ProcessCpuUtilization(pid)),
      uptime_(LinuxParser::UpTime(pid)) {}

// DONE: Return this process's ID
int Process::Pid() { return pid_; }

// DONE: Return this process's CPU utilization
float Process::CpuUtilization() {
  long uptime = LinuxParser::UpTime(pid_);
  vector<string> process_stats = LinuxParser::ProcessCpuUtilization(pid_);

  float prev_total_time =
      std::stof(process_stats_[LinuxParser::ProcessCPUStates::kUtime_]) +
      std::stof(process_stats_[LinuxParser::ProcessCPUStates::kStime_]);

  float total_time =
      std::stof(process_stats[LinuxParser::ProcessCPUStates::kUtime_]) +
      std::stof(process_stats[LinuxParser::ProcessCPUStates::kStime_]);

  float total_time_diff = total_time - prev_total_time;
  long uptime_diff = uptime - uptime_;

  cpu_utilization_ = (total_time_diff / sysconf(_SC_CLK_TCK)) / uptime_diff;

  process_stats_ = process_stats;
  uptime_ = uptime;

  return cpu_utilization_;
}

// DONE: Return the command that generated this process
string Process::Command() { return LinuxParser::Command(pid_); }

// DONE: Return this process's memory utilization
string Process::Ram() { return LinuxParser::Ram(pid_); }

// DONE: Return the user (name) that generated this process
string Process::User() { return LinuxParser::User(pid_); }

// DONE: Return the age of this process (in seconds)
long int Process::UpTime() { return LinuxParser::UpTime(pid_); }

// DONE: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process const& a) const {
  return (100 * a.cpu_utilization_) < (100 * this->cpu_utilization_);
}
