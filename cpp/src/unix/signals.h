/**************************************************\
* The MIT License (MIT)
* Copyright (c) 2014 Kevin Walchko
* see LICENSE for full details
\**************************************************/
#pragma once

// #include <functional>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/*
https://stackoverflow.com/questions/1641182/how-can-i-catch-a-ctrl-c-event
https://www.geeksforgeeks.org/inheritance-in-c/
https://stackoverflow.com/questions/12662891/how-can-i-pass-a-member-function-where-a-free-function-is-expected

http://www.yolinux.com/TUTORIALS/C++Signals.html
*/
/*
kevin@Logan build $ kill -l
 1) SIGHUP	 2) SIGINT	 3) SIGQUIT	 4) SIGILL
 5) SIGTRAP	 6) SIGABRT	 7) SIGEMT	 8) SIGFPE
 9) SIGKILL	10) SIGBUS	11) SIGSEGV	12) SIGSYS
13) SIGPIPE	14) SIGALRM	15) SIGTERM	16) SIGURG
17) SIGSTOP	18) SIGTSTP	19) SIGCONT	20) SIGCHLD
21) SIGTTIN	22) SIGTTOU	23) SIGIO	24) SIGXCPU
25) SIGXFSZ	26) SIGVTALRM	27) SIGPROF	28) SIGWINCH
29) SIGINFO	30) SIGUSR1	31) SIGUSR2

https://www.linusakesson.net/programming/tty/

SIGHUP - terminate on hangup condition
SIGINT - terminate, ^C
SIGQUIT - core dump, ^\
SIGPIPE - terminate, write to pipe with no readers
SIGCHLD - ignore, when a child process dies or changes state
SIGSTOP - suspend, ^Z, application suspends
SIGCONT - wake up, un-suspends a stopped process
SIGSTP - suspend, ^Z, suspends a process
*/

#if defined __cplusplus
extern "C" {
#endif


void signal_capture(int signal, void (*func)(int)) {
  struct sigaction sigIntHandler;
  sigIntHandler.sa_handler = func;
  sigemptyset(&sigIntHandler.sa_mask);
  sigIntHandler.sa_flags = 0;
  sigaction(signal, &sigIntHandler, NULL);
}


#if defined __cplusplus
}
#endif
