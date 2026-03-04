/* This program demonstrate the implementation of basic condition variable. The main thread spins while `done == 0`.
 * `child` function runs which updates `done` to 1 then during the next scheduling of the main thread it stops
 * spinning since `done == 0` doesn't satisfies thus executing the next line of code.
 * */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

volatile int done = 0;

void *child(void *arg) {
  done = 0;
  printf("im child\n");
  done = 1;
  return NULL;
}

int main(void) {
  pthread_t th;
  printf("start\n");
  pthread_create(&th, NULL, child, NULL);
  pthread_create(&th, NULL, child, NULL);
  // for (long i = 0; i < 10; i++)
  //   printf("i: %ld\n", i);

  while (done == 0)
    ;
  // pthread_join( th, NULL);
  printf("end\n");
  return 0;
}
