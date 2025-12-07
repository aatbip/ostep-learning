// Concurrent counter

#include <assert.h>
#include <pthread.h>
#include <stdatomic.h>
#include <stdio.h>
#include <stdlib.h>

double get_time_ms() {
  struct timespec ts;
  clock_gettime(CLOCK_MONOTONIC, &ts);
  return (double)ts.tv_sec * 1000.0 + (double)ts.tv_nsec / 1000000.0;
}

void Pthread_mutex_init(pthread_mutex_t *mutex) {
  int i = pthread_mutex_init(mutex, NULL);
  assert(i == 0);
}
void Pthread_mutex_lock(pthread_mutex_t *mutex) {
  int i = pthread_mutex_lock(mutex);
  assert(i == 0);
}
void Pthread_mutex_unlock(pthread_mutex_t *mutex) {
  int i = pthread_mutex_unlock(mutex);
  assert(i == 0);
}

typedef struct __counter_t {
  int count;
  pthread_mutex_t mutex;
} counter_t;

void init(counter_t *c) {
  c->count = 0;
  Pthread_mutex_init(&c->mutex);
}

void incr(counter_t *c) {
  pthread_mutex_lock(&c->mutex);
  c->count++;
  Pthread_mutex_unlock(&c->mutex);
}

void decr(counter_t *c) {
  Pthread_mutex_lock(&c->mutex);
  c->count--;
  Pthread_mutex_unlock(&c->mutex);
}

int getcount(counter_t *c) {
  Pthread_mutex_lock(&c->mutex);
  int count = c->count;
  pthread_mutex_unlock(&c->mutex);
  return count;
}

void *routine(void *t) {
  for (int i = 0; i < 1000000; i++) {
    incr((counter_t *)(t));
  }
  return NULL;
}

void Pthread_create(pthread_t *th, void *p) {
  int i = pthread_create(th, NULL, routine, p);
  assert(i == 0);
}
void Pthread_join(pthread_t th) {
  int i = pthread_join(th, NULL);
  assert(i == 0);
}

void run_threads(int n, counter_t *counter) {
  pthread_t *th = malloc(sizeof(pthread_t) * n);

  for (int i = 0; i < n; i++) {
    Pthread_create(&th[i], counter);
  }

  for (int i = 0; i < n; i++) {
    Pthread_join(th[i]);
  }

  free(th);
}

int main(void) {
  counter_t *counter = malloc(sizeof(*counter));
  init(counter);
  if (!counter)
    return 1;

  double start = get_time_ms();
  run_threads(512, counter);
  double end = get_time_ms();

  // double start = get_time_ms();
  // for (int i = 0; i < 500000000; i++) {
  //   incr(counter);
  // }
  // double end = get_time_ms();

  printf("count: %d\n", getcount(counter));
  printf("time taken: %f\n", end - start);

  free(counter);

  return 0;
}
