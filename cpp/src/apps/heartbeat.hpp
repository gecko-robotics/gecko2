/**************************************************\
* The MIT License (MIT)
* Copyright (c) 2014 Kevin Walchko
* see LICENSE for full details
\**************************************************/
#pragma once

// #include <gciSensors.hpp>
#include "alarm.hpp"
#include "gecko2/messages.hpp"

class Heartbeat : public Alarm {
public:
  Heartbeat() {
    msg.id            = 1;
    msg.has_autopilot = 0;
  }

  bool init(const uint16_t sensors) {
    msg.sensors = sensors;
    return true;
  }

  const heartbeat_t get_msg() {
    msg.timestamp = millis();
    return msg;
  }

protected:
  heartbeat_t msg;
};