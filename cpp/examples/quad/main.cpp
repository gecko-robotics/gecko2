
/*
FIXME: Issues not sure of
- remove neopixel from system.hpp ... but how to include?
*/

// declare in mock_serial as true if not defined
// declare in serialcomm as false if not defined
#define USE_GCIMOCK_SERIAL  0
#ifndef apple
  #define apple __APPLE__
#endif

#include <gecko2/boards/generic/generic.hpp>
#include <mock_arduino.hpp>
#include <mock_wire.hpp>
#include <serialcomm/mock_serial.hpp>
#include <serialcomm/serial.hpp>
#include <gecko2.hpp>

Stream Serial;
Stream Serial1;
TwoWire Wire; // how work on linux?

// Arduino code below /////////////////////////////////////////////
#if defined(ARDUINO)
#include <gecko2/boards/adafruit/Adafruit_ItsyBitsy_M4.hpp>
#endif

#include <gecko2.hpp>
#include <yivo.hpp>
#include "imu.hpp"
// #include "tf.hpp"

Yivo yivo; // uC to computer packetizer
// Serializer msp;
kalman_filter kf;

constexpr int IMU_USE_UNCALIBRATED_DATA = 0;

#if HAS_NEOPIXEL
  #include <Adafruit_NeoPixel.h>
#endif

// quadcopter system
// System q; // rename or derive a class?

// sensors
gciLSOXLISBMP imu;
// gciTFmini tfmini(1);

void setup() {
  bool ready;

  Serial.begin(1000000);
  Serial.setTimeout(5);
  while (!Serial)
    delay(10);

  Serial1.begin(TFmini::DEFAULT_BAUDRATE);

  // imu.enable(ALARM_100_HZ);
  // tfmini.enable(ALARM_10_HZ);

  // q.sensors.push_back(&imu);
  // q.sensors.push_back(&tfmini);

  // for heartbeat
  uint16_t sensors = heartbeat_t::ACCEL;
  sensors |= heartbeat_t::GYRO;
  sensors |= heartbeat_t::BAROMETER;
  sensors |= heartbeat_t::TEMPERATURE;
  sensors |= heartbeat_t::RANGE;
  sensors |= heartbeat_t::BATTERY;
  sensors |= heartbeat_t::COMPASS;
  // bool ready = q.init(sensors, BOARD_MOTOR_PINS, *BOARD_USB_SERIAL);

  while (!ready) {
    Serial.println("Error initializing System"); // change to yivo message?
    delay(1000);
  }

  kalman_filter_init(&kf, 0.001, 0.0,0.0,0.0,1.0);
}

void loop() {
  // Serial.println("hello");

  // q.loop();
}

int main() {
  setup();

  while (true)
    loop();

  return 0;
}

// class cSensor {
//   public:
//   cSensor(): found(false) {}
//   virtual bool init() =0;
//   virtual void read() =0;
//   virtual void send_msg() =0;

//   bool found;
//   // uint8_t msg_id;
//   // std::function<void(uint8_t,uint8_t*,std::size_t)> func;
//   // std::function<void(Yivo<128>&,uint8_t,uint8_t*,std::size_t)> func;
// };

// class tImu: public cSensor {
//   public:
//   tImu(): cSensor() {}
//   bool init() {
//     found = true;
//     return true;
//   }
//   void read() {}
//   void send_msg() {
//     if(!found) return;
//     yivo.pack_n_send(100, reinterpret_cast<uint8_t*>(&msg), sizeof(ImuA_t));
//     // func(100, reinterpret_cast<uint8_t*>(&msg), sizeof(ImuA_t));
//   }

//   ImuA_t msg;
//   // std::function<void(uint8_t,uint8_t*,std::size_t)> func;
// };
