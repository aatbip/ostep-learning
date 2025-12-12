#include <assert.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <threads.h>

typedef struct m1 {
  int x, y;
} m1_t;

typedef struct my_ret {
  int a, b;
} my_ret_t;

void *routine(void *arg) {
  m1_t *m1 = (m1_t *)arg;
  printf("I am routine: %d %d\n", m1->x, m1->y);

  my_ret_t *ret = malloc(sizeof(*ret));
  ret->a = 21;
  ret->b = 22;
  return (void *)ret;
}

int main(void) {
  pthread_t t1;
  int rc;
  m1_t arg = {.x = 10, .y = 12};
  my_ret_t *ret;

  rc = pthread_create(&t1, NULL, routine, &arg);
  assert(rc == 0);
  rc = pthread_join(t1, (void **)&ret);
  assert(rc == 0);
  printf("returned: %d %d\n", ret->a, ret->b);

  return 0;
}
