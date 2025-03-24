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

Process::Process(int pid) : pid_(pid) {}

// DONE: Return this process's ID
int Process::Pid() { return pid_; }

// DONE: Return this process's CPU utilization
float Process::CpuUtilization() {
  long uptime = LinuxParser::UpTime(pid_);
  string line, discard;
  long utime, stime, cutime, cstime, random;
  std::ifstream filestream(LinuxParser::kProcDirectory + to_string(pid_) +
                           LinuxParser::kStatFilename);
  if (filestream.is_open()) {
    std::getline(filestream, line);
    std::istringstream linestream(line);
    for (int i = 1; i <= 13; i++) {
      linestream >> discard;
    }
    linestream >> utime >> stime >> cutime >> cstime >> random;
    float total_time = utime + stime;
    total_time += cutime + cstime;
    cpu_utilization_ = (total_time / sysconf(_SC_CLK_TCK)) / uptime;
    return cpu_utilization_;
  }
  return 0.0;
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
  return a.cpu_utilization_ < this->cpu_utilization_;
}
