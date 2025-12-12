/* Here we solve the producer/consumer (bounded buffer) problem using semaphore.
 * This program creates a producer/consumer buffer using semaphore.*/
#include <semaphore.h>
#include <stdlib.h>

#define MAX 10

int buffer[MAX];
int pc = 0; // producer count
int cc = 0; // consumer count

sem_t p, c;

void *producer(void *arg) {

  buffer[pc] = rand();
  pc = (pc + 1) % MAX;
  pc++;

  return NULL;
}

int main(void) { return 0; }
