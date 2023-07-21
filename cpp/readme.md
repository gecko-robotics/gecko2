![](docs/header.jpg)

# Gecko 2

In the neverending re-writes of my software ... here is a new version of `gecko`

```cpp
#define USE_GCIMOCK_SERIAL 1 // to use fake serial
#include <gecko2.hpp>
```

Thinking of organizing like this:

```
include/gecko2
 |
 +- <linux/mac files for computers>
 +- logger
 +- network (udp/uds)
 +- serializer (yivo w/udp)
 +- signals
 +- time
 +- camera_streaming
 +- arduino <files for uC>
     |
     +- gecko2
     +- boards/
     |   |
     |   +- adafruit/board
     +- leds/
     |   |
     |   +- blinkingled
     +- imu
     +- autopilot
     +- blackbox
     +- heartbeat
     +- sensors
     +- serializer (yivo w/Arduino serial)
     +- state
     +- toggle
```

## Structure

- uC flies UAV
    - autopilot (simple): level hover, takeoff and land
        - FSM for managing UAV system
        - This autopilot is more of an emergency autopilot to save the vehicle
    - manual: direct control via joystick or RPi ... UAV won't know difference
    - sensor publishing via serial to more advanced system
    - complementary filter to hover
- RPi
    - autopilot (advanced): waypoint gps, complex control
    - publishing via UDP/UDS
    - advanced sensor filtering
        - EKF
    - camera control and publishing

## Libraries

- `yivo` for serial and udp serialization and standard messages
- `serialcomm` for linux/mac serial
    - linux/mac serial testing mock interface with `serial_mock`
- `gciMock` for linux/mac/Arduino testing
    - testing:
        - linux/mac will simulate Arduino functions, i2c
    - linux runtime
        - Arduino like i2c interface
    - mac/linux
        -
- `squaternion` for quaternions
- `gciSensors` for Arduino i2c and serial sensors
- `marko` for udp/uds communications

## `cmake`

```cmake
set(BUILD_EXAMPLES OFF CACHE INTERNAL "Dont build examples")
set(BUILD_GTESTS OFF CACHE INTERNAL "Dont build tests")
```

## Todo

- [x] Move to header only library
- [ ] General UAV state machine
- [ ] Quad controller
- [ ] EKF for sensor navigation
- [ ] Teleoperations with joystick

---

# Mavlink

```
[motor]<---[esc]<---[uC pwm]<--->[pi serial]
[imu/bar/temp]<--->[uC i2c]<--->[pi serial]
[tfmini]--->[pi]
[camera]--->[pi csi]
```


| Process   | Message(`MAVLINK_MSG_ID_`) | ID  | PUB_Hz / SUB |
|-----------|----------------------------|-----|--------------|
| autopilot | `MANUAL_CONTROL`           | 69  | S   |
|           | `HEARTBEAT`                | 0   | 1   |
|           | `HIGHRES_IMU`              | 105 | 100 |
|           | `ATTITUDE_QUATERNION`      | 31  | 100 |
|           | `BATTERY_STATUS`           | 147 | 1   |
|           | `POWER_STATUS`             | 125 | 1   |
| camera    | `VISION_POSITION_ESTIMATE` | 102 | 20  |
|           | `VISION_SPEED_ESTIMATE`    | 103 | 20  |
| ins       | `GPS_RAW_INT`              | 24  | S   |
|           | `ATTITUDE_QUATERNION`      | 31  | S   |
|           | `VISION_POSITION_ESTIMATE` | 102 | S   |
|           | `VISION_SPEED_ESTIMATE`    | 103 | S   |
|           | `HIGHRES_IMU`              | 105 | S   |
|           | `LOCAL_POSITION_NED`       | 32  | 50  |
| TFmini    | `DISTANCE_SENSOR`          | 132 |     |


So some of these seem stupid. Might make my own dialect (add new)
messages, but would now be incompatabile with others ... not sure.

- New messages
    - `MAVLINK_MSG_ID_POSE`
        - time_usec, position[m], velocity[m/s], attitude[q]
        - replace: `LOCAL_POSITION_NED`, `ATTITUDE_QUATERNION`
            - also replace the `VISION` one too
    - `MAVLINK_MSG_ID_SYS_POWER`
        - time_usec, battery[V], 3V3[V], 5V[V], 12V[V], capacity[V]
        - not sure about the various 3v3v, 5v, 12v ... do they add value?
          can I measure them good enough with a 3v3 uC?


- [`mavlink` messages](https://mavlink.io/en/messages/common.html)
- github [C library v2](https://github.com/mavlink/c_library_v2)
- python [`pymavlink](https://mavlink.io/en/mavgen_python/)
    - `pip install pymavlink lxml future`
- github [image transmission protocol](https://mavlink.io/en/services/image_transmission.html)
    ```python
    >>> from pymavlink import mavutil
    >>> mavutil.mavlink20() # are we using v2?
    False
    >>> mavutil.mavlink10() # are we using v1?
    True
    ```
- [eigen3 EKF](https://github.com/mherb/kalman)

```
https://github.com/mavlink/mavros/issues/305

mavlink stream -d /dev/ttyS6 -s PARAM_VALUE -r 300
mavlink stream -d /dev/ttyS6 -s MISSION_ITEM -r 50
mavlink stream -d /dev/ttyS6 -s NAMED_VALUE_FLOAT -r 10
mavlink stream -d /dev/ttyS6 -s OPTICAL_FLOW_RAD -r 10
mavlink stream -d /dev/ttyS6 -s VFR_HUD -r 20
mavlink stream -d /dev/ttyS6 -s ATTITUDE -r 20
mavlink stream -d /dev/ttyS6 -s ACTUATOR_CONTROL_TARGET0 -r 30
mavlink stream -d /dev/ttyS6 -s RC_CHANNELS_RAW -r 5
mavlink stream -d /dev/ttyS6 -s SERVO_OUTPUT_RAW_0 -r 20
mavlink stream -d /dev/ttyS6 -s POSITION_TARGET_GLOBAL_INT -r 10
mavlink stream -d /dev/ttyS6 -s LOCAL_POSITION_NED -r 30
mavlink stream -d /dev/ttyS6 -s MANUAL_CONTROL -r 5
mavlink stream -d /dev/ttyS6 -s HIGHRES_IMU -r 100
mavlink stream -d /dev/ttyS6 -s GPS_RAW_INT -r 20
```

## Customm Quadcopters

- [arduino quadcopter](https://www.instructables.com/Arduino-micro-Quadcopter/)
    - [github](https://github.com/Montvydas/MonteQuadcopter)

## Libraries

- UDP pub/sub: [marko](https://github.com/gecko-robotics/marko.cpp)
- [C mavlink v2](https://github.com/mavlink/c_library_v2)
- [serial port lib](https://github.com/gecko-robotics/serialcomm)
- [msgpack](https://github.com/hideakitai/MsgPacketizer)
- [embeded STL](https://github.com/ETLCPP/etl)

## Interesting Things

- [MsgPack serializer for arduino](https://github.com/hideakitai/MsgPacketizer)
- [Degbug logger](https://github.com/hideakitai/DebugLog)
- [Dynamixel for arduino](https://github.com/hideakitai/Dynamixel)
- [RP2040 servo headers and Qwiic header](https://www.adafruit.com/product/5437)

## messages

- mavlink
    - create own dialect: https://mavlink.io/en/getting_started/generate_libraries.html
    - custom messages: https://docs.px4.io/main/en/middleware/mavlink.html

- BFS Mavlink: https://github.com/bolderflight/mavlink

- hackflight
    - python parser that reads json to create messages: https://github.com/simondlevy/Hackflight/tree/master/parser


# MIT License

**Copyright (c) 2014 gecko-robotics**

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.