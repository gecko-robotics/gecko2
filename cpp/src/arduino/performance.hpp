/**************************************************\
* The MIT License (MIT)
* Copyright (c) 2014 Kevin Walchko
* see LICENSE for full details
\**************************************************/
#pragma once

/**
This doesn't work right ... wtf?
*/
struct Performance {
  Performance(uint32_t hz=1): ready(hz) {
    epoch = millis();
    count = 0;
  }

  inline bool update() {
    return (++count >= ready);
  }

  float get_hz() {
    uint32_t now = millis();
    float hz = 1000.0f / float(now - epoch);
    epoch = now;
    count = 0;
    return hz;
  }

  uint32_t epoch;
  uint32_t count;
  const uint32_t ready;
};