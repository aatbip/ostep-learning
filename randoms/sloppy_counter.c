// sloppy counter
#include <assert.h>
#include <bits/pthreadtypes.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define CPUTHREADS 12 // total threads in the cpu
#define THRESHOLD 128

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
  int gcount;             // global count
  pthread_mutex_t gmutex; // global lock
  /* local count and lock is array of size CPUTHREADS because each thread maintains its own count*/
  int lcount[CPUTHREADS];             // local count
  pthread_mutex_t lmutex[CPUTHREADS]; // local lock
} counter_t;

void init(counter_t *counter) {
  counter->gcount = 0;
  pthread_mutex_init(&counter->gmutex, NULL);
  for (int i = 0; i < CPUTHREADS; i++) {
    counter->lcount[i] = 0;
    pthread_mutex_init(&counter->lmutex[i], NULL);
  }
}

void incr(counter_t *counter, short threadID, int threshold) {
  pthread_mutex_lock(&counter->lmutex[threadID]);
  counter->lcount[threadID]++;
  if (counter->lcount[threadID] >= threshold) {
    pthread_mutex_lock(&counter->gmutex);
    counter->gcount += counter->lcount[threadID];
    counter->lcount[threadID] = 0;
    pthread_mutex_unlock(&counter->gmutex);
  }
  pthread_mutex_unlock(&counter->lmutex[threadID]);
}

int get_global_counter(counter_t *counter) {
  pthread_mutex_lock(&counter->gmutex);
  int val = counter->gcount;
  pthread_mutex_unlock(&counter->gmutex);
  return val;
}

typedef struct {
  counter_t *counter;
  short threadID;
} routine_arg_t;

void *routine(void *arg) {
  routine_arg_t *r = (routine_arg_t *)arg;
  for (int i = 0; i < 1000000; i++) {
    incr(r->counter, r->threadID, THRESHOLD);
  }
  return NULL;
}

void run_threads(counter_t *counter, int n) {
  routine_arg_t *arg = malloc(sizeof(*arg) * n);
  pthread_t *th = malloc(sizeof(pthread_t) * n);
  for (int i = 0; i < n; i++) {
    (arg + i)->threadID = i % CPUTHREADS;
    // printf("threadid: %d\n", (arg + i)->threadID);
    (arg + i)->counter = counter;
    pthread_create(&th[i], NULL, routine, (void *)(arg + i));
  }
  for (int i = 0; i < n; i++) {
    pthread_join(th[i], NULL);
  }
  free(th);
}

int main(void) {
  counter_t *counter = malloc(sizeof(*counter));
  init(counter);
  int start = get_time_ms();
  run_threads(counter, 500);
  float end = get_time_ms();
  printf("counter: %d\n", get_global_counter(counter));
  printf("time taken: %f\n", end - start);
  free(counter);
  return 0;
}
