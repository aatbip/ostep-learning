/* This program demonstrates the order violation bug. */

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

int main(void) {
  sys_t *sys = (sys_t *)malloc(sizeof(*sys));
  sys->node = malloc(sizeof(*sys->node) * 12);
  strcpy(sys->node, "hello");
  return 0;
}
