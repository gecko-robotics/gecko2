#include <gecko2.hpp>
#include <gtest/gtest.h>
#include <stdio.h>

// state
namespace None {
constexpr fsm_state_t state = 0;
bool conditionN2I(void) { return true; }
void onEnter() { printf("in None\n"); }
void onExit() { printf("leaving None -> "); }
}

namespace Initial {
constexpr fsm_state_t state = 1;
bool conditionI2A(void) {return true;}
bool conditionI2N(void) {return false;}
void onEnter() { printf("in Initial\n"); }
void onExit() { printf("leaving Initial -> "); }
}

namespace A {
constexpr fsm_state_t state = 2;
bool conditionA2B(void) {return true;}
void onEnter() { printf("in A\n"); }
void onExit() { printf("leaving A -> "); }
}

namespace B {
constexpr fsm_state_t state = 3;
bool conditionB2A(void) {return true;}
void onEnter() { printf("in B\n"); }
void onExit() { printf("leaving B -> "); }
}

TEST(fsm, run) {

  FSM<10> fsm; // number of states

  // Add some transitions
  fsm.addTransition(None::state, Initial::state, None::conditionN2I, None::onExit, Initial::onEnter);
  fsm.addTransition(Initial::state, A::state, Initial::conditionI2A, Initial::onExit, A::onEnter);
  fsm.addTransition(Initial::state, None::state, Initial::conditionI2N, Initial::onExit, None::onEnter); // never happen
  fsm.addTransition(A::state, B::state, A::conditionA2B, A::onExit, B::onEnter);
  fsm.addTransition(B::state, A::state, B::conditionB2A, B::onExit, A::onEnter);

  // Set the initial state.
  fsm.init(None::state, None::onEnter);
  EXPECT_EQ(fsm.state(), None::state);

  // run!
  fsm.run();
  EXPECT_EQ(fsm.state(), Initial::state);
  fsm.run();
  EXPECT_EQ(fsm.state(), A::state);
  fsm.run();
  EXPECT_EQ(fsm.state(), B::state);

  for (int i=0; i<10; ++i) {
    fsm.run();
    if (i%2 == 0) EXPECT_EQ(fsm.state(), A::state);
    else EXPECT_EQ(fsm.state(), B::state);
  }
}