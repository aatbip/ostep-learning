#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct __arg {
  sem_t *s;
} arg_t;

void *child(void *arg) {
  sem_t *s = ((arg_t *)arg)->s;
  printf("I am child!\n");
  sem_post(s);
  return NULL;
}

int main(void) {
  printf("start\n");
  pthread_t th;
  sem_t s;
  arg_t *arg = malloc(sizeof(*arg));
  arg->s = &s;
  sem_init(&s, 0, 0);
  pthread_create(&th, NULL, child, (void *)arg);
  sem_wait(&s);
  free(arg);
  printf("end\n");
  return 0;
}
