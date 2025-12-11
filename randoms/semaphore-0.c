/*Binary semaphore - semaphore as locks
 * We can use semaphore as a lock where we initialize the semaphore with X as 1.
 * sem_init($s, 0, X) where X = 1 which will act as a lock to protect critical section.*/
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>

int count = 0; // shared resource

typedef struct __counter {
  sem_t s;
} counter_t;

void *counter(void *arg) {

  count++;
  return NULL;
}

void spwan_thread(int n) {
  pthread_t *th = malloc(sizeof(*th) * n);
  for (int i = 0; i < 5; i++) {
    pthread_create(&th[i], NULL, counter, NULL);
  }
  for (int i = 0; i < 5; i++) {
    pthread_join(th[i], NULL);
  }
}

int main(void) {
  sem_t s;
  /*Semaphore is initialized to value 1 in the 3rd parameter below.
   * Second parameter is 0 indicating that this semaphore will be
   * used within the threads created from the same process.*/
  sem_init(&s, 0, 1);
}
