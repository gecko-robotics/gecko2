/**************************************\
 * The MIT License (MIT)
 * Copyright (c) 2022 Kevin Walchko
 * see LICENSE for full details
\**************************************/
#pragma once

#include <math.h>
#include <stdint.h>

#ifndef __UNITS_HPP__
#define __UNITS_HPP__

#if defined(ARDUINO)
  typedef float dorf;
#else
  typedef double dorf;
#endif

namespace Units {

// Angular
constexpr dorf rad2deg = 180.0 / M_PI;
constexpr dorf deg2rad = M_PI / 180.0;
constexpr dorf rps2rpm = 0.0;     // FIXME
constexpr dorf rpm2rps = 0.10472; // FIXME

// Magnetism
constexpr dorf gauss2tesla = 1e-5;
constexpr dorf tesla2gauss = 1e5;

// Pressure
constexpr dorf STD_PRESSURE_PA = 101325.0;                   // Pa
constexpr dorf pa2atm = 9.86923e-6;
constexpr dorf atm2pa = 101325.0;

// Temperature
inline dorf f2c(dorf f) { return 0.5555556 * (f - 32.0); }
inline dorf c2f(dorf c) { return 1.8 * c + 32.0; }
inline dorf c2k(dorf c) { return c + 273.15; }
inline dorf k2c(dorf k) { return k - 273.15; }

// Distance
constexpr dorf m2mi  = 0.000621371; // meters to miles
constexpr dorf mi2m  = 1609.34;     // miles to meters
constexpr dorf km2mi = 0.621371;
constexpr dorf mi2km = 1.60934;
constexpr dorf ft2m  = 0.3048; // feet to meters

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
// inline dorf decimal_date(uint8_t yr, uint8_t mon, uint8_t day) {
//   return static_cast<dorf>(yr) + static_cast<dorf>(mon) / 12.0f +
//          static_cast<dorf>(day) / 30.0f;
// }

} // namespace Units

#endif