/* This program demonstrates the order violation bug. */

#include <bits/pthreadtypes.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct sys {
  char *node;
} sys_t;

void *init(void *arg) {
  sys_t *sys = (sys_t *)arg;
  sys = malloc(sizeof(*sys->node) * 12); // initialize sys->node
  return NULL;
}

void *append_print(void *arg) {
  sys_t *sys = (sys_t *)arg;
  strcpy(sys->node, "hello");
  printf("node: %s\n", sys->node);
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
