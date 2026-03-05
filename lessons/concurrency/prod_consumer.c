/* This program implements the bounded buffer (producer consuemer queue) with the help of CV and mutex for thread
 * synchronization.
 * */

#include <assert.h>
#include <bits/pthreadtypes.h>
#include <pthread.h>
#include <stdint.h>
#include <stdio.h>

int buffer = -1;
int count = 0;
pthread_cond_t cv_get = PTHREAD_COND_INITIALIZER;
pthread_cond_t cv_put = PTHREAD_COND_INITIALIZER;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void put(int v) {
  printf("putting\n");
  count = 1;
  buffer = v;
}

int get() {
  count = 0;
  return buffer;
}

void *producer(void *arg) {
  intptr_t n = (intptr_t)arg;
  for (int i = 0; i < n; i++) {
    pthread_mutex_lock(&mutex);
    while (count > 0) {
      pthread_cond_wait(&cv_put, &mutex);
    }
    put(i);
    pthread_cond_signal(&cv_get);
    pthread_mutex_unlock(&mutex);
  }
  return NULL;
}

void *consumer(void *arg) {
  intptr_t n = (intptr_t)arg;
  while (1) {
    pthread_mutex_lock(&mutex);
    while (count == 0) {
      pthread_cond_wait(&cv_get, &mutex);
    }
    int tmp = get();
    pthread_cond_signal(&cv_put);
    pthread_mutex_unlock(&mutex);
    printf("%d\n", tmp);
    if (tmp == n - 1)
      break;
  }
  return NULL;
}

int main(void) {
  pthread_t th_prod;
  pthread_t th_cons;
  pthread_create(&th_prod, NULL, producer, (void *)10);
  pthread_create(&th_cons, NULL, consumer, (void *)10);
  pthread_join(th_prod, NULL);
  pthread_join(th_cons, NULL);
  return 0;
}
