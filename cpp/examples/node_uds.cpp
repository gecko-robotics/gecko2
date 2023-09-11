#include <cstdint>
#include <gecko2.hpp>
#include <iostream>

using namespace std;

class Node {
  public:
  Node(): s(sizeof(accel_t)) {}

  void pub() {
    // string path{"unix://./ps.uds"};
    // unixaddr_t addr = unix_sockaddr(path);
    unixaddr_t addr = unix_sockaddr();
    p.register_addr(addr);
    while (true) {
      accel_t d{1,2,3};
      message_t m = pack<accel_t>(d);
      p.publish(m);
      // cout << "." << flush;
      msleep(100);
    }
  }

  static
  void callback(const message_t& m) {
    static int i = 0;
    accel_t d = unpack<accel_t>(m);
    cout << i++ << " " << d.accel.x << " " << d.accel.y  << " " << d.accel.z << endl;
  }

  void sub() {
    // string path{"unix://./ps.uds"};
    // unixaddr_t addr = unix_sockaddr(path);
    unixaddr_t addr = unix_sockaddr();
    s.bind(addr);
    s.register_cb( Node::callback );
    while (true) {
      s.once();
    }
  }

  PublisherUnix p;
  SubscriberUnix s;
};

void pub_thread() {
  Node node;
  node.pub();
}

void sub_thread() {
  Node node;
  node.sub();
}

int main() {
  thread subth(sub_thread);
  marko::msleep(1);
  thread pubth(pub_thread);

  subth.join();
  pubth.join();

  return 0;
}
