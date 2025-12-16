/* This program demonstrates the atomicity violation bug. */
#include <stdio.h>

typedef struct sys {
  int node;
} sys_t;

void *t1(void *arg) {
  sys_t *sys = (sys_t *)arg;
  printf("node: %d\n", sys->node);
  return NULL;
}

int main(void) { sys_t sys; }
