/**************************************************\
* The MIT License (MIT)
* Copyright (c) 2014 Kevin Walchko
* see LICENSE for full details
\**************************************************/

#pragma once

#include <Arduino.h>

namespace gecko {

inline void msleep(int msec) { delay(msec); }
inline void usleep(int usec) { delayMicroseconds(usec); }
inline void sleep(int sec) { delay(1000 * sec); }

inline uint32_t mtime() { return millis(); }
inline uint32_t utime() { return micros(); }


} // namespace gecko