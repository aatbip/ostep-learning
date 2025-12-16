/* This program demonstrates the order violation bug. */

#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct sys {
  char *node;
} sys_t;

bool initialized = false;
pthread_cond_t cv = PTHREAD_COND_INITIALIZER;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *init(void *arg) {
  sys_t *sys = (sys_t *)arg;
  pthread_mutex_lock(&mutex);
  sys->node = malloc(sizeof(*sys->node) * 12); // initialize sys->node
  initialized = true;
  pthread_cond_signal(&cv);
  pthread_mutex_unlock(&mutex);
  return NULL;
}

void *append_print(void *arg) {
  sys_t *sys = (sys_t *)arg;
  pthread_mutex_lock(&mutex);
  while (!initialized) {
    pthread_cond_wait(&cv, &mutex);
  }
  /* We can introduce a long running loop here so that kernel will
   * context switch at this point to the init thread so that
   * initialization of `node` completes. This is just a demonstration
   * but not a method that should be employ for real. We will instead
   * use CV. */
  // for (int i = 0; i < 100000; i++)
  //   ;
  strcpy(sys->node, "hello");
  printf("node: %s\n", sys->node);
  pthread_mutex_unlock(&mutex);
  return NULL;
}

int main(void) {
  sys_t *sys = (sys_t *)malloc(sizeof(*sys));
  pthread_t th1, th2;

  pthread_create(&th1, NULL, init, (void *)sys);
  pthread_create(&th2, NULL, append_print, (void *)sys);

  pthread_join(th1, NULL);
  pthread_join(th2, NULL);
  return 0;
}
