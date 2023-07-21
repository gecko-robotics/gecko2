/**************************************************\
* The MIT License (MIT)
* Copyright (c) 2014 Kevin Walchko
* see LICENSE for full details
\**************************************************/
#pragma once


#include <stdint.h>

// msec
constexpr uint32_t ALARM_1_HZ   = 1000;
constexpr uint32_t ALARM_5_HZ   = 200;
constexpr uint32_t ALARM_10_HZ  = 100;
constexpr uint32_t ALARM_20_HZ  = 50;
constexpr uint32_t ALARM_25_HZ  = 40;
constexpr uint32_t ALARM_50_HZ  = 20;
constexpr uint32_t ALARM_100_HZ = 10;
constexpr uint32_t ALARM_200_HZ = 5;

/*
Returns true after a set amount of time (in msec) has ellapsed.

Don't like the name ... Timer?

ISR library:
https://github.com/Dennis-van-Gils/SAMD51_InterruptTimer
*/
class Alarm {
public:
  Alarm() : enabled(false), epoch(0), dt(0) {}

  void enable(const uint32_t delaytime) {
    if (enabled) return;
    dt      = delaytime;
    epoch   = millis();
    enabled = true;
  }

  void disable() { enabled = false; }

  inline operator bool() { return check(); }

  bool check() {
    uint32_t now = millis();
    if (now >= epoch) {
      epoch = now + dt;
      return true;
    }
    return false;
  }

protected:
  uint32_t dt;
  uint32_t epoch;
  bool enabled;
};