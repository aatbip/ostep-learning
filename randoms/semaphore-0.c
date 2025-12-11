/*Binary semaphore - semaphore as locks
 * We can use semaphore as a lock where we initialize the semaphore with X as 1.
 * sem_init($s, 0, X) where X = 1 which will act as a lock to protect critical section.*/

#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>

double get_time_ms() {
  struct timespec ts;
  clock_gettime(CLOCK_MONOTONIC, &ts);
  return (double)ts.tv_sec * 1000.0 + (double)ts.tv_nsec / 1000000.0;
}

int count = 0; // shared resource
//
// pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

typedef struct __counter {
  sem_t *s;
} counter_t;

void *counter(void *arg) {
  sem_t *s = ((counter_t *)arg)->s;
  for (int i = 0; i < 1000000; i++) {
    sem_wait(s);
    // pthread_mutex_lock(&mutex);
    count++;
    // pthread_mutex_unlock(&mutex);
    sem_post(s);
  }
  return NULL;
}

void spwan_thread(sem_t *s, int n) {
  pthread_t *th = malloc(sizeof(*th) * n);
  counter_t *arg = malloc(sizeof(*arg) * n);
  for (int i = 0; i < n; i++) {
    (arg + i)->s = s;
    pthread_create(&th[i], NULL, counter, (void *)(arg + i));
  }
  for (int i = 0; i < n; i++) {
    pthread_join(th[i], NULL);
  }
  free(th);
  free(arg);
}

int main(void) {
  sem_t s;
  /*Semaphore is initialized to value 1 in the 3rd parameter below.
   * Second parameter is 0 indicating that this semaphore will be
   * used within the threads created from the same process.*/
  sem_init(&s, 0, 1);
  double start = get_time_ms();
  spwan_thread(&s, 50);
  double end = get_time_ms();
  printf("time: %f\n", end - start);
  printf("counter: %d\n", count);
  return 0;
}
