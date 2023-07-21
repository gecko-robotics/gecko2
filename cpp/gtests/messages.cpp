#include <gecko2.hpp>
#include <gtest/gtest.h>


TEST(messages, basics) {
  vec_t v = {1., 2., 3.};
  EXPECT_EQ(v.x, 1.0);
  EXPECT_EQ(v.y, 2.0);
  EXPECT_EQ(v.z, 3.0);
  EXPECT_TRUE(sizeof(vec_t) == 3 * sizeof(float));

  EXPECT_TRUE(sizeof(quaternion_t) == 4 * sizeof(float));
}