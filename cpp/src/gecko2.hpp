/**************************************************\
* The MIT License (MIT)
* Copyright (c) 2014 Kevin Walchko
* see LICENSE for full details
\**************************************************/
#pragma once

/*
Organization:

arduino - only for Arduino boards, this should be small
unix - only for computers/sbc that run unix/linux/bsd/macos
gecko2 - for either arduinos or computers
*/

#include <messages.hpp>

// #if defined(ARDUINO_ITSYBITSY_M0)
// #include "gecko2/boards/adafruit/Adafruit_ItsyBitsy_M0.hpp"
// // #elif defined(__SAMD51__)
// #elif defined(ARDUINO_ITSYBITSY_M4)
// #include "gecko2/boards/adafruit/Adafruit_ItsyBitsy_M4.hpp"
// #elif defined(__APPLE__) || defined(linux)
// #include "gecko2/boards/generic/generic.hpp"
// #endif

#if defined(ARDUINO)
  #include "arduino/time.hpp"
#endif

#if defined(UNIX) || defined(linux) || defined(__APPLE__)
  #include "unix/colors.hpp"
  #include "unix/signals.hpp"
  #include "unix/time.hpp"
  #include <marko/marko.hpp>
  #include <gunther.hpp>
#endif

#include "blackbox.hpp"
#include "fsm.hpp"
#include "toggle.hpp"
#include "vector.hpp"
#include "return_type.hpp"
#include "units.hpp"
