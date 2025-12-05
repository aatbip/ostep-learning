#include <assert.h>
#include <bits/pthreadtypes.h>
#include <pthread.h>
#include <stdatomic.h>
#include <stdio.h>

static volatile int counter = 0;
static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER; // shared mutex

void *my_thread(void *arg) {
  printf("%s: begin\n", (char *)arg);
  pthread_mutex_lock(&mutex);
  for (int i = 0; i < 1e7; i++) {
    counter += 1;
  }
  pthread_mutex_unlock(&mutex);
  printf("%s: done\n", (char *)arg);
  return NULL;
}

int main(void) {
  pthread_t t1, t2;
  int rc;
  printf("main: begin\n");
  rc = pthread_create(&t1, NULL, my_thread, "A");
  assert(rc == 0);
  rc = pthread_create(&t2, NULL, my_thread, "B");
  assert(rc == 0);
  rc = pthread_join(t1, NULL);
  assert(rc == 0);
  rc = pthread_join(t2, NULL);
  assert(rc == 0);
  printf("Final result of counter: %d\n", counter);
  printf("main: end\n");
  return 0;
}
