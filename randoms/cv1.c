#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

volatile int done = 0;

void *child(void *arg) {
  printf("im child\n");
  done = 1;
  return NULL;
}

int main(void) {
  pthread_t th;
  printf("start\n");
  pthread_create(&th, NULL, child, NULL);
  // for (long i = 0; i < 10; i++)
  //   printf("i: %ld\n", i);

  while (done == 0)
    ;
  // pthread_join( th, NULL);
  printf("end\n");
  return 0;
}
