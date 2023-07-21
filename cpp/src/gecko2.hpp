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

// #ifndef USE_GCIMOCK_SERIAL
//   #define USE_GCIMOCK_SERIAL 1
// #endif

// #if USE_GCIMOCK_SERIAL
//   #include <mock_serial.hpp>
// #elif defined(ARDUINO)
// #else
//   #include <serialcomm/serial.hpp>
// #endif

#include "defaults.hpp"


// #if defined(ARDUINO_ITSYBITSY_M0)
// #include "gecko2/boards/adafruit/Adafruit_ItsyBitsy_M0.hpp"
// // #elif defined(__SAMD51__)
// #elif defined(ARDUINO_ITSYBITSY_M4)
// #include "gecko2/boards/adafruit/Adafruit_ItsyBitsy_M4.hpp"
// #elif defined(__APPLE__) || defined(linux)
// #include "gecko2/boards/generic/generic.hpp"
// #endif

#if defined(UNIX) || defined(linux) || defined(__APPLE__)
  #include "unix/colors.hpp"
  #include "unix/logger.hpp"
  #include "unix/signals.hpp"
  #include "unix/time.hpp"
  // #include "unix/network.hpp"

  // udp communications - leave out?
  // #include <marko/udpsocket.hpp>
  // #include <marko/utils.hpp>

// serial communications
// #include <serialcomm/serial.hpp>
#endif

#if defined(ARDUINO)
  #include "arduino/leds/blinkled.hpp"
  #include "arduino/performance.hpp"
  #include "arduino/time.hpp"
  // #include <Servo.h>
// #else
  // #include <mock_arduino.hpp>
  // #include <mock_servo.hpp>
#endif

#include "apps/alarm.hpp"
#include "apps/heartbeat.hpp"

#include "gecko2/blackbox.hpp"
#include "gecko2/messages.hpp"
#include "gecko2/fsm.hpp"
#include "gecko2/toggle.hpp"
#include "gecko2/kf.hpp"

// small savings over STL containers, this only
// does fixed size arrays
#include "containers/vector.hpp"

// deprecated
// #include "gecko2/motors.hpp"
// #include "gecko2/sensor.hpp"
// #include "gecko2/serializer.hpp"
// #include "gecko2/system.hpp"
// #include "gecko2/autopilot.hpp"