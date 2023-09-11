#include <cstdint>
#include <gecko2.hpp>
#include <iostream>

using namespace std;

class Node {
  public:
  Node(): s(sizeof(accel_t)) {}

  void pub() {
    string path{"udp://0.0.0.0:9000"};
    inetaddr_t addr = inet_sockaddr(path);
    p.reuseSocket(true);
    p.register_addr(addr);
    p.bind(addr);
    while (true) {
      accel_t d{1,2,3};
      message_t m = pack<accel_t>(d);
      p.publish(m);
      // cout << "." << flush;
      msleep(100);
    }
  }

  // static
  // void callback(const message_t& m) {
  //   static int i = 0;
  //   accel_t d = unpack<accel_t>(m);
  //   cout << d.accel.x << endl;
  // }

  void sub() {
    string path{"udp://127.0.0.1:9000"};
    inetaddr_t addr = inet_sockaddr(path);
    s.connect(addr);
    // s.register_cb( Node::callback ); // could do a callback
    while (true) {
      // s.once();
      message_t m = s.recv(sizeof(accel_t));
      accel_t d = unpack<accel_t>(m);
      cout << d.accel.x << " " << d.accel.y  << " " << d.accel.z << endl;
    }
  }

  PublisherUDP p;
  SubscriberUDP s;
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
