/**************************************************\
* The MIT License (MIT)
* Copyright (c) 2014 Kevin Walchko
* see LICENSE for full details
\**************************************************/
#pragma once


/**
Simple Toggle class that allows you to toggle a state
variable on/off.
*/
class Toggle {
public:
  Toggle(bool v = false) : val(v) {}

  bool toggle() {
    val = !val;
    return val;
  }

  void set(bool v) { val = v; }

  explicit operator bool() const { return val; }

protected:
  bool val;
};