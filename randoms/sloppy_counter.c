// sloppy counter
#include <assert.h>
#include <bits/pthreadtypes.h>
#include <pthread.h>

#define CPUTHREADS 12 // total threads in the cpu

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
