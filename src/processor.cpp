#include "processor.h"

#include <string>

#include "linux_parser.h"

Processor::Processor() : cpu_stats_(LinuxParser::CpuUtilization()) {}

// DONE: Return the aggregate CPU utilization
float Processor::Utilization() {
  std::vector<std::string> cpu_stats = LinuxParser::CpuUtilization();

  float PrevIdle = std::stof(cpu_stats_[LinuxParser::CPUStates::kIdle_]) +
                   std::stof(cpu_stats_[LinuxParser::CPUStates::kIOwait_]);

  float Idle = std::stof(cpu_stats[LinuxParser::CPUStates::kIdle_]) +
               std::stof(cpu_stats[LinuxParser::CPUStates::kIOwait_]);

  float PrevNonIdle = std::stof(cpu_stats_[LinuxParser::CPUStates::kUser_]) +
                      std::stof(cpu_stats_[LinuxParser::CPUStates::kNice_]) +
                      std::stof(cpu_stats_[LinuxParser::CPUStates::kSystem_]) +
                      std::stof(cpu_stats_[LinuxParser::CPUStates::kIRQ_]) +
                      std::stof(cpu_stats_[LinuxParser::CPUStates::kSoftIRQ_]) +
                      std::stof(cpu_stats_[LinuxParser::CPUStates::kSteal_]);

  float NonIdle = std::stof(cpu_stats[LinuxParser::CPUStates::kUser_]) +
                  std::stof(cpu_stats[LinuxParser::CPUStates::kNice_]) +
                  std::stof(cpu_stats[LinuxParser::CPUStates::kSystem_]) +
                  std::stof(cpu_stats[LinuxParser::CPUStates::kIRQ_]) +
                  std::stof(cpu_stats[LinuxParser::CPUStates::kSoftIRQ_]) +
                  std::stof(cpu_stats[LinuxParser::CPUStates::kSteal_]);

  float PrevTotal = PrevIdle + PrevNonIdle;
  float Total = Idle + NonIdle;

  float totald = Total - PrevTotal;
  float idled = Idle - PrevIdle;

  cpu_stats_ = cpu_stats;
  return (totald - idled) / totald;
}
