/* This code demonstrates deadlock. */
#include <pthread.h>
#include <stdio.h>

int i = 0;
int j = 0;

pthread_mutex_t mutex_i = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex_j = PTHREAD_MUTEX_INITIALIZER;

void *t1(void *arg) {
  pthread_mutex_lock(&mutex_i);
  i += 1;
  pthread_mutex_lock(&mutex_j);
  j += 1;
  pthread_mutex_unlock(&mutex_j);
  pthread_mutex_unlock(&mutex_i);

  return NULL;
}

void *t2(void *arg) {
  pthread_mutex_lock(&mutex_j);
  j += 1;
  pthread_mutex_lock(&mutex_i);
  i += 1;
  pthread_mutex_unlock(&mutex_i);
  pthread_mutex_unlock(&mutex_j);

  return NULL;
}

int main(void) {
  pthread_t th1, th2;
  pthread_create(&th1, NULL, t1, NULL);
  pthread_create(&th2, NULL, t1, NULL);

  pthread_join(th1, NULL);
  pthread_join(th2, NULL);

  printf("i: %d\n", i);
  printf("j: %d\n", j);

  return 0;
}
