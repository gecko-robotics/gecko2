#include <gecko2.hpp>
#include <gtest/gtest.h>
#include <stdio.h>

using namespace gecko;

TEST(vector, basic) {
  vector<int, 10> v;
  EXPECT_EQ(v.max_size(), 10);

  v[0] = 123;
  v[1] = -456;
  v[2] = 789;

  EXPECT_EQ(v.size(), 3);
  EXPECT_EQ(v.len(), 3);

  int *p = v.data();

  EXPECT_EQ(p[0], 123);
  EXPECT_EQ(p[1], -456);
  EXPECT_EQ(p[2], 789);

  v.clear();
  EXPECT_EQ(v.size(), 0);
  EXPECT_EQ(v.len(), 0);

  v.push_back(123);
  v.push_back(-456);
  v.push_back(789);

  EXPECT_EQ(v.size(), 3);
  EXPECT_EQ(v.len(), 3);

  p = v.data();

  EXPECT_EQ(p[0], 123);
  EXPECT_EQ(p[1], -456);
  EXPECT_EQ(p[2], 789);
}

TEST(vector, iterators) {
  vector<int, 10> v;
  EXPECT_EQ(v.max_size(), 10);

  for (int i=0; i < 100; i++) {
    v[i] = 42;
    int a = v[i];
    EXPECT_EQ(a, 42);
  }

  for (const int &d: v) EXPECT_EQ(d, 42);
}