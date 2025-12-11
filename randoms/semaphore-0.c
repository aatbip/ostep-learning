#include <semaphore.h>

int main(void) {
  sem_t s;
  /*Semaphore is initialized to value 1 in the 3rd parameter below.
   * Second parameter is 0 indicating that this semaphore will be
   * used within the threads created from the same process.*/
  sem_init(&s, 0, 1);
}
