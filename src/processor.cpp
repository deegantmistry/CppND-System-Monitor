#include "processor.h"

#include <sstream>
#include <string>

#include "linux_parser.h"

Processor::Processor() {
  std::string line, key;
  std::ifstream filestream(LinuxParser::kProcDirectory +
                           LinuxParser::kStatFilename);
  if (filestream.is_open()) {
    getline(filestream, line);
    std::istringstream linestream(line);
    linestream >> key >> user_ >> nice_ >> system_ >> idle_ >> iowait_ >>
        irq_ >> softirq_ >> steal_ >> guest_ >> guest_nice_;
  }
}

// DONE: Return the aggregate CPU utilization
float Processor::Utilization() {
  std::string line, key;
  std::ifstream filestream(LinuxParser::kProcDirectory +
                           LinuxParser::kStatFilename);
  if (filestream.is_open()) {
    float user, nice, system, idle, iowait, irq, softirq, steal, guest,
        guest_nice;

    getline(filestream, line);
    std::istringstream linestream(line);
    linestream >> key >> user >> nice >> system >> idle >> iowait >> irq >>
        softirq >> steal >> guest >> guest_nice;

    float PrevIdle = idle_ + iowait_;
    float Idle = idle + iowait;

    float PrevNonIdle = user_ + nice_ + system_ + irq_ + softirq_ + steal_;
    float NonIdle = user + nice + system + irq + softirq + steal;

    float PrevTotal = PrevIdle + PrevNonIdle;
    float Total = Idle + NonIdle;

    float totald = Total - PrevTotal;
    float idled = Idle - PrevIdle;

    return (totald - idled) / totald;
  }

  return 0.0;
}
