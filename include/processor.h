#ifndef PROCESSOR_H
#define PROCESSOR_H
#include <string>
#include <vector>

class Processor {
 public:
  Processor();
  float Utilization();  // DONE: See src/processor.cpp

  // DONE: Declare any necessary private members
 private:
  std::vector<std::string> cpu_stats_;
};

#endif
