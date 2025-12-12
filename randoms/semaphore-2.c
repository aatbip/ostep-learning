/* Here we solve the producer/consumer (bounded buffer) problem using semaphore.
 * This program creates a producer/consumer buffer using semaphore.*/
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX 10

int buffer[MAX];
int pc = 0; // producer count
int cc = 0; // consumer count

sem_t p, c, mutex;

void put(int n) {
  buffer[pc] = n;
  pc = (pc + 1) % MAX;
}

int get() {
  int tmp = buffer[cc];
  cc = (cc + 1) % MAX;
  return tmp;
}

void *producer(void *arg) {
  put(rand());
  return NULL;
}

void *consumer(void *arg) {
  int tmp = get();
  printf("consumed: %d\n", tmp);
  return NULL;
}

int main(void) {
  sem_init(&p, 0, MAX);
  sem_init(&c, 0, 0);
  sem_init(&mutex, 0, 1);
  return 0;
}
