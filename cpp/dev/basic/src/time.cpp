
#include "time.hpp"

// #include <ctime>
#include <thread>

using namespace std::chrono;
using namespace std;


long Time::now(){
    auto now_ms = time_point_cast<milliseconds>(system_clock::now());
    auto epic = now_ms.time_since_epoch();
    long time = epic.count();
    return time;
}

// google::protobuf::Timestamp Time::unixNow(){}

google::protobuf::Timestamp Time::unix(){
    struct timeval tv;
    gettimeofday(&tv, NULL);
    google::protobuf::Timestamp timestamp;
    timestamp.set_seconds(tv.tv_sec);
    timestamp.set_nanos(tv.tv_usec * 1000);  // tv.tv_usec is micro seconds
    return timestamp;
}

void Time::msleep(int msec){
    this_thread::sleep_for(chrono::milliseconds(msec));
}

void Time::sleep(int sec){
    this_thread::sleep_for(chrono::seconds(sec));
}

//////////////////////////////////////////////////////////////////////

Rate::Rate(double hertz){
    last_time = time_point_cast<milliseconds>(system_clock::now());
    // dt = std::chrono::milliseconds(int(1000/hertz));
    dt = milliseconds(int(1000/hertz));

    // cout << dt.count() << endl;
    //
    // // last_time = time_point_cast<milliseconds>(system_clock::now());
    //
    // std::this_thread::sleep_for(std::chrono::milliseconds(100));
    //
    // auto now = time_point_cast<milliseconds>(system_clock::now());
    //
    // auto diff = duration_cast<std::chrono::milliseconds>(now - last_time);
    //
    // // cout << now << endl;
    // //
    // // cout << last_time << endl;
    //
    // cout << diff.count() << endl;
    // // cout << diff << endl;
}

void Rate::sleep(void){
    auto now = time_point_cast<milliseconds>(system_clock::now());

    auto diff = duration_cast<std::chrono::milliseconds>(now - last_time);
    if (diff < dt){
        this_thread::sleep_for(dt - diff);
    }
    last_time = time_point_cast<milliseconds>(system_clock::now());
}
