#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <unix/signals.h>


bool run = true;

void func(int sig) {
  printf("func arg: %d\n", sig);
  run = false;
}

int main() {
  printf("hello\n");

  signal_capture(SIGINT, func);

  while(run);

  return 0;
}