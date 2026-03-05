/* This program demonstrates the atomicity violation bug. */
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct sys {
  char *node;
} sys_t;

// pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *t1(void *arg) {
  sys_t *sys = (sys_t *)arg;
  // pthread_mutex_lock(&mutex);
  if (sys->node) {
    /* We are forcing context switch to occur at this time by running a time consuming long loop.
     * Now, t2 will run and overwrite `node` to NULL which will bring seg fault error in fputs().*/
    for (int i = 0; i < 100000; i++)
      ;
    fputs(sys->node, stdout);
  }
  // pthread_mutex_unlock(&mutex);
  return NULL;
}

void *t2(void *arg) {
  sys_t *sys = (sys_t *)arg;
  // pthread_mutex_lock(&mutex);
  sys->node = NULL;
  // pthread_mutex_unlock(&mutex);
  return NULL;
}

int main(void) {
  sys_t *sys = (sys_t *)malloc(sizeof(*sys));
  sys->node = malloc(sizeof(*sys->node) * 12);
  strcpy(sys->node, "working?\n");

  pthread_t th1, th2;
  pthread_create(&th1, NULL, t1, (void *)sys);
  pthread_create(&th2, NULL, t2, (void *)sys);

  pthread_join(th2, NULL);
  pthread_join(th1, NULL);

  return 0;
}
