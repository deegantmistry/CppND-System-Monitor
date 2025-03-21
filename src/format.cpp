#include "format.h"

#include <string>

using std::string;

// DONE: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long seconds) {
  string result = "";
  int h, m, s;

  h = seconds / 3600;
  m = (seconds % 3600) / 60;
  s = seconds % 60;
  return ((h < 10 ? "0" : "") + std::to_string(h) + ":" + (m < 10 ? "0" : "") +
          std::to_string(m) + ":" + (s < 10 ? "0" : "") + std::to_string(s));
}
