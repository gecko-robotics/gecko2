#include <gecko2.hpp>
#include <gtest/gtest.h>
#include <stdio.h>

struct BBMsg_t {
  std::string msg;
  int err;
};

TEST(blackbox, basic) {
  Blackbox<BBMsg_t, 10> bb;
  EXPECT_TRUE(bb.empty());
  EXPECT_FALSE(bb.full());

  BBMsg_t msg{"hi", 10};
  for (int i = 0; i < 100; ++i) {
    msg.err = i % 10;
    bb.push_back(msg);
  }
  EXPECT_FALSE(bb.empty());
  EXPECT_TRUE(bb.full());
  EXPECT_EQ(bb.size(), 10);
  EXPECT_EQ(bb.len(), 10);

  // printf("%d %d\n", bb.head(), bb.tail());
  for (int i = 0; i < 10; i++) {
    // printf("%d %d %d\n", i, bb.head(), bb.tail());
    EXPECT_EQ(bb[i].err, i);
  }

  EXPECT_TRUE(0 == bb.front().err);
  EXPECT_TRUE(9 == bb.back().err);
}

TEST(blackbox, position) {
  Blackbox<BBMsg_t, 10> bb;

  BBMsg_t msg{"hi", 10};
  for (int i = 0; i < 10; ++i)
    bb.push_back(msg);

  // printf("%d %d\n", bb.tail(), bb.size());

  BBMsg_t *m        = bb.data();
  const BBMsg_t *m2 = bb.data();
  EXPECT_TRUE(m == m2);
  EXPECT_TRUE(0 == bb.head());
  EXPECT_TRUE(9 == bb.tail());

  bb.push_back(msg);
  EXPECT_TRUE(1 == bb.head());
  EXPECT_TRUE(0 == bb.tail());

  bb.push_back(msg);
  EXPECT_TRUE(2 == bb.head());
  EXPECT_TRUE(1 == bb.tail());
}