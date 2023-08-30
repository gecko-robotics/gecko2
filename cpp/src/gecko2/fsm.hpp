/**************************************************\
* The MIT License (MIT)
* Copyright (c) 2014 Kevin Walchko
* see LICENSE for full details
\**************************************************/
#pragma once

#include <array>
#include <stdint.h>
#include <stdio.h>

/*
States:
- boot - power up and get everything ready
- idle - unarmed, post-boot
- armed - can command motors
- autopilot - autonomous flight to waypoints
- manual - joystick control
- shutdown - power everything down and switch off
*/

typedef uint8_t fsm_state_t;

// Transitions
// {from, to, condition, exitFrom, enterTo}
struct Transition {
  fsm_state_t from;
  fsm_state_t to;

  // std::function<bool(void)> condition;
  // std::function<void(void)> onExit;
  // std::function<void(void)> onEnter;

  bool (*condition)(void); // these save a LOT of memory 2.2KB
  void (*onExit)(void);
  void (*onEnter)(void);
};

// State machine
template <const uint8_t FSM_SIZE> class FSM {
public:
  FSM() : state_(0), array_ptr(0) {}

  void init(fsm_state_t state, void (*on_enter)(void)) {
    if (on_enter != nullptr) on_enter();
    state_ = state;
  }

  bool addTransition(fsm_state_t from, fsm_state_t to, bool (*condition)(void),
                     void (*on_exit)(void), void (*on_enter)(void)) {
    if (array_ptr == FSM_SIZE) return false;
    if (on_enter == nullptr || on_exit == nullptr) return false;
    transitions_[array_ptr++] =
        Transition{from, to, condition, on_exit, on_enter};
    return true;
  }

  // void SetState(fsm_state_t state, std::function<void(void)> onexit,
  // std::function<void(void)> onenter) {
  void setState(fsm_state_t state, void (*on_exit)(void),
                void (*on_enter)(void)) {
    if (state != state_) {
      on_exit();
      on_enter();
      state_ = state;
    }
  }

  void run() {
    // Check if there are any transitions that match the current state.
    // for (const Transition& transition : transitions_) {
    for (size_t i = 0; i < array_ptr; ++i) {
      const Transition &transition = transitions_[i];
      // printf("%d\n",transition.from);
      if ((transition.from == state_) && transition.condition()) {
        // Transition to the new state.
        setState(transition.to, transition.onExit, transition.onEnter);
        // printf("break: %d -> %d\n",transition.from,transition.to);

        // Break out of the loop.
        break;
      }
    }
  }

  inline const fsm_state_t state() const { return state_; }

protected:
  size_t array_ptr;
  fsm_state_t state_;
  std::array<Transition, FSM_SIZE> transitions_;
};