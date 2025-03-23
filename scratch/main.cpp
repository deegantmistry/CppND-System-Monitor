#include <unistd.h>

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
using std::string;

long UpTime() {
  string line;
  long uptime{0};
  std::ifstream filestream("/proc/uptime");
  if (filestream.is_open()) {
    std::getline(filestream, line);
    std::istringstream linestream(line);
    linestream >> uptime;
  }
  return uptime;
}

long UpTime(int pid) {
  string line, uptime;
  std::ifstream filestream("/proc/" + std::to_string(pid) + "/stat");
  if (filestream.is_open()) {
    std::getline(filestream, line);
    std::istringstream linestream(line);
    for (int i = 0; i <= 21; i++) {
      linestream >> uptime;
    }
  }
  // return 0;
  long process_uptime = UpTime() - (std::stol(uptime) / sysconf(_SC_CLK_TCK));
  std::cout << "starttime: " << uptime << "\n";
  std::cout << "Uptime: " << process_uptime << "\n";

  return process_uptime;
}

int main() {
  int pid_ = 14312;
  long uptime = UpTime(pid_);
  string line, discard;
  long utime, stime, cutime, cstime, random;
  std::ifstream filestream("/proc/" + std::to_string(pid_) + "/stat");
  if (filestream.is_open()) {
    std::getline(filestream, line);
    std::istringstream linestream(line);
    for (int i = 0; i <= 12; i++) {
      linestream >> discard;
    }
    linestream >> utime >> stime >> cutime >> cstime >> random;
    long total_time = utime + stime;
    total_time += cutime + cstime;

    std::cout << "utime: " << utime << "\n";
    std::cout << "stime: " << stime << "\n";
    std::cout << "cutime: " << cutime << "\n";
    std::cout << "cstime: " << cstime << "\n";
    std::cout << "total time: " << total_time << "\n";

    std::cout << "Hertz: " << sysconf(_SC_CLK_TCK) << "\n";
    std::cout << "Process uptime: " << uptime << "\n";

    float cpu_utilization_ = 100 * (total_time / sysconf(_SC_CLK_TCK)) / uptime;
    std::cout << "CPU utilization of process " << pid_ << " = "
              << cpu_utilization_ << "\n";
  }
  // std::cout << "Printing 0: " << 0 << "\n";
}
