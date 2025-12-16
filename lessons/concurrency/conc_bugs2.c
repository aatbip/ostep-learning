/* This code demonstrates deadlock.
 * All 4 of the Coffman's conditions should meet for a deadlock to occur.
 * 1. Mutual exclusion - We have added mutex_i and mutex_j.
 * 2. Hold-and-wait - Both t1 and t2 holds the mutex and wait until
 * they complete incrementing the variables i and j.
 * 3. No preemption - Mutex are not unlocked from anywhere else. Or there
 * are no conditions like `trylock` to check if mutex was lock and then recover.
 * 4. Circular wait - t2 wait for t1 to unlock mutex_i and t1 waits for t2 to unlock
 * mutex_j. There is a circular wait.*/

#include <pthread.h>
#include <stdio.h>

int i = 0;
int j = 0;

pthread_mutex_t mutex_i = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex_j = PTHREAD_MUTEX_INITIALIZER;

void *t1(void *arg) {
  pthread_mutex_lock(&mutex_i);
  i += 1;
  /* We add a long loop so that kernel will context switch at this point.
   * This context switch will satisfy Coffman's condition of circular wait
   * for deadlock.*/
  for (int i = 0; i < 100000; i++)
    ;
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
  pthread_create(&th2, NULL, t2, NULL);

  pthread_join(th1, NULL);
  pthread_join(th2, NULL);

  printf("i: %d\n", i);
  printf("j: %d\n", j);

  return 0;
}
