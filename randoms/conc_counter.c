// Concurrent counter

#include <assert.h>
#include <pthread.h>
#include <stdatomic.h>
#include <stdio.h>
#include <stdlib.h>

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

int main(void) {
  counter_t *counter = malloc(sizeof(*counter));
  if (!counter)
    return 1;

  init(counter);
  incr(counter);
  incr(counter);
  incr(counter);
  incr(counter);
  decr(counter);
  printf("count: %d\n", getcount(counter));

  return 0;
}
