/**************************************\
 * The MIT License (MIT)
 * Copyright (c) 2022 Kevin Walchko
 * see LICENSE for full details
\**************************************/
#pragma once

#include <math.h>
#include <stdint.h>

namespace Units {

// Angular
constexpr double rad2deg = 180.0 / M_PI;
constexpr double deg2rad = M_PI / 180.0;
constexpr double rps2rpm = 0.0;     // FIXME
constexpr double rpm2rps = 0.10472; // FIXME

// Magnetism
constexpr double gauss2tesla = 1e-5;
constexpr double tesla2gauss = 1e5;

// Pressure
constexpr double STD_PRESSURE_PA = 101325.0;                   // Pa
constexpr double pa2atm = 9.86923e-6;
constexpr double atm2pa = 101325.0;

// Temperature
inline double f2c(double f) { return 0.5555556 * (f - 32.0); }
inline double c2f(double c) { return 1.8 * c + 32.0; }
inline double c2k(double c) { return c + 273.15; }
inline double k2c(double k) { return k - 273.15; }

// Distance
constexpr double m2mi  = 0.000621371; // meters to miles
constexpr double mi2m  = 1609.34;     // miles to meters
constexpr double km2mi = 0.621371;
constexpr double mi2km = 1.60934;
constexpr double ft2m  = 0.3048; // feet to meters

// // bits/bytes ... useful?
// static uint16_t to_b16(const uint8_t b[2], const bool little = true) {
//   union {
//     uint16_t s;   // short
//     uint8_t b[2]; // byte
//   } buff;

//   if (little) {
//     buff.b[0] = b[0];
//     buff.b[1] = b[1];
//   }
//   else {
//     buff.b[0] = b[1];
//     buff.b[1] = b[0];
//   }

//   return buff.s;
// }

/*
 * Need to fix day for 29, 30, 31 days
 *
 * Is this useful?
 */
// inline double decimal_date(uint8_t yr, uint8_t mon, uint8_t day) {
//   return static_cast<double>(yr) + static_cast<double>(mon) / 12.0f +
//          static_cast<double>(day) / 30.0f;
// }

} // namespace Units