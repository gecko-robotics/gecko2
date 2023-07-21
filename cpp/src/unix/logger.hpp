/**************************************************\
* The MIT License (MIT)
* Copyright (c) 2014 Kevin Walchko
* see LICENSE for full details
\**************************************************/
#pragma once

#include "colors.hpp"
#include <iostream>

/*
todo:
- add logging levels
- add ability to write to file
- add ability to write binary mavlink_messages_t???
- add custom message instead of "alt", up to 5 char, ex: imuAx, gyro2, cam0, etc
...
*/
class Logger {
public:
  void debug(std::string s) {
    std::string ts = timestamp();
    std::cout << Back.GREEN + Fore.WHITE << "[" << ts << "|Debug]" << Fore.RESET
              << " " << s << std::endl;
  }

  void info(std::string s) {
    std::string ts = timestamp();
    std::cout << Back.CYAN + Fore.WHITE << "[" << ts << "|Info ]" << Fore.RESET
              << " " << s << std::endl;
  }
  void warn(std::string s) {
    std::string ts = timestamp();
    std::cout << Back.YELLOW + Fore.BLACK << "[" << ts << "|Warn ]"
              << Fore.RESET << " " << s << std::endl;
  }

  void error(std::string s) {
    std::string ts = timestamp();
    std::cout << Back.RED + Fore.WHITE << "[" << ts << "|Error]" << Fore.RESET
              << " " << s << std::endl;
  }

  void alt1(std::string s) {
    std::string ts = timestamp();
    std::cout << Back.WHITE + Fore.BLACK << "[" << ts << "|Alt  ]" << Fore.RESET
              << " " << s << std::endl;
  }
  void alt2(std::string s) {
    std::string ts = timestamp();
    std::cout << Back.MAGENTA + Fore.WHITE << "[" << ts << "|Alt  ]"
              << Fore.RESET << " " << s << std::endl;
  }
  void alt3(std::string s) {
    std::string ts = timestamp();
    std::cout << Back.BLUE + Fore.WHITE << "[" << ts << "|Alt  ]" << Fore.RESET
              << " " << s << std::endl;
  }

  std::string timestamp() {
    // Time output taken from:
    // https://stackoverflow.com/questions/16357999#answer-16358264
    time_t rawtime;
    time(&rawtime);
    struct tm *timeinfo = localtime(&rawtime);
    char time_buffer[10]{}; // We need 8 characters + \0
    strftime(time_buffer, sizeof(time_buffer), "%I:%M:%S", timeinfo);
    return time_buffer;
  }
};

// #include <gecko/gecko.hpp>
// #include <string>

// class Logger {
// public:
//     enum LogTypes {
//         STDOUT=1,
//         TCP   =2,
//         UDS   =4
//     };

//     // Logger(int type=0);
//     Logger(); // stdout
//     Logger(std::string key, std::string topic, bool tcp=true); // tcp
//     // Logger(std::string file); // uds

//     // void print(const std::string& s) const {}
//     void logerror(const std::string& s) const;
//     void logwarn(const std::string& s) const;
//     void loginfo(const std::string& s) const;
//     void logdebug(const std::string& s) const;

// protected:
//     void log(const std::string& s) const; // printf
//     Publisher *publisher;
//     int type;
// };

// class LogPub : public Logger {
// public:
//     // create publisher that will send measages to the main logger
//     LogPub(std::string& key, bool bind=false) {}
// protected:
//     void log(const std::string& s) const; // pub to server
// };

// class LogSub : public Logger {
// public:
//     // create subscriber that will receive all log measages
//     LogSub(std::string& key, bool bind=false) {}
// // protected:
// //     void log(const std::string& s) const; // printf
// };
