#pragma once

// #include <gciSensors.hpp>
// #include "board.h"
// #include "Adafruit_ItsyBitsy_M0.hpp"

#include "apps/alarm.hpp"

// constexpr int BOARD_LED_PIN = 13;
constexpr int wait_time = 500;

// Toggle board's LED on/off
class BlinkLED : public Alarm {
public:
  BlinkLED(const uint8_t pin, const uint32_t delaytime)
      : pin(pin), led_blink(true) {}

  void update() {
    if (check()) {
      led(led_blink);
      led_blink = !led_blink;
    }
  }

protected:
  void led(bool val) {
    if (val) digitalWrite(pin, HIGH);
    else digitalWrite(pin, LOW);
  }

  bool led_blink;
  uint8_t pin;
};

//////////////////////////////////////////

// class Hertz {
//   public:
//   Hertz(const uint32_t delaytime): mark(millis()), dt(delaytime) {}

//   bool check(){
//     uint32_t now = millis();
//     if (now > mark){
//       mark = now + dt;
//       return true;
//     }
//     return false;
//   }

//   protected:
//   const uint32_t dt;
//   uint32_t mark;
// };
