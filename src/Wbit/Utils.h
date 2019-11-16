#ifndef Utils_h
#define Utils_h

#include "Arduino.h"

#ifdef DEBUG_ESP_PORT
#define DEBUG_MSG(...) DEBUG_ESP_PORT.printf(__VA_ARGS__)
#else
#define DEBUG_MSG(...)
#endif

class Utils {
 public:
  static String boolStr(bool b) { return b ? "true" : "false"; }
};

#endif