#ifndef PROCESSOR_H
#define PROCESSOR_H

class Processor {
 public:
  Processor();
  float Utilization();  // DONE: See src/processor.cpp

  // DONE: Declare any necessary private members
 private:
  float user_, nice_, system_, idle_, iowait_, irq_, softirq_, steal_, guest_,
      guest_nice_;
};

#endif
