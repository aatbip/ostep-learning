/*Binary semaphore - semaphore as locks
 * We can use semaphore as a lock where we initialize the semaphore with X as 2.
 * sem_init($s, 0, X) where X = 2 which will act as a lock to protect critical section.*/
#include <semaphore.h>
#include <stdio.h>

int main(void) {
  sem_t s;
  /*Semaphore is initialized to value 1 in the 3rd parameter below.
   * Second parameter is 0 indicating that this semaphore will be
   * used within the threads created from the same process.*/
  sem_init(&s, 0, 1);
  int p = sem_wait(&s);
  int q = sem_post(&s);
  printf("p: %d, q: %d\n", p, q);
}
