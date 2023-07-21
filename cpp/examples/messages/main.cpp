#include <cstdint>
#include <gecko2.hpp>
#include <iostream>

using namespace std;

int main() {
  cout << "Standard types:" << endl;
  cout << "  int:" << sizeof(int) << " " << sizeof(unsigned int) << " "
       << sizeof(uint32_t) << endl;
  cout << "  ulong: " << sizeof(long) << " " << sizeof(unsigned long) << " "
       << sizeof(int64_t) << endl;
  cout << "  float: " << sizeof(float) << endl;
  cout << "  double: " << sizeof(double) << endl;
  cout << "Messages:" << endl;
  cout << "  vec_t: " << sizeof(vec_t) << endl;
  cout << "  header_t: " << sizeof(header_t) << endl;
  // cout << "  imu_raw_t: " << sizeof(imu_raw_t) << endl;
  cout << "  imu_full_t: " << sizeof(imu_full_t) << endl;
  cout << "  quaternion_t: " << sizeof(quaternion_t) << endl;

  return 0;
}
