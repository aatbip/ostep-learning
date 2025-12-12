/* Here we solve the producer/consumer (bounded buffer) problem using semaphore.
 * This program creates a producer/consumer buffer using semaphore.*/
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX 10
#define THREADS 15
#define LOOP 5

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
  for (int i = 1; i <= LOOP; i++) {
    sem_wait(&p);
    sem_wait(&mutex); // add lock
    put(i);
    sem_post(&mutex);
    sem_post(&c);
  }
  return NULL;
}

void *consumer(void *arg) {
  for (int i = 1; i <= LOOP; i++) {
    sem_wait(&c);
    sem_wait(&mutex); // add lock
    int tmp = get();
    printf("consumed: %d\n", tmp);
    sem_post(&mutex);
    sem_post(&p);
  }
  return NULL;
}

int main(void) {
  /* Initialize with MAX because size of the buffer is MAX and logically
   * if sem_wait(&p) decrements MAX to become -1 then producer should
   * wait.*/
  sem_init(&p, 0, MAX);
  /* Initialize with 0 because in the beginning there are 0 items
   * in the buffer. Logically, let's say if consumer runs first,
   * then it will wait at sem_wait(&c) since 0 decrements to -1. */
  sem_init(&c, 0, 0);
  /* Initialized to 1 to create a binary semaphore working as a mutex lock. */
  sem_init(&mutex, 0, 1);
  pthread_t *th_p = malloc(sizeof(*th_p) * THREADS);
  pthread_t *th_c = malloc(sizeof(*th_c) * THREADS);
  for (int i = 0; i < THREADS; i++) {
    pthread_create(&th_p[i], NULL, producer, NULL);
  }
  for (int i = 0; i < THREADS; i++) {
    pthread_create(&th_c[i], NULL, consumer, NULL);
  }
  for (int i = 0; i < THREADS; i++) {
    pthread_join(th_p[i], NULL);
  }
  for (int i = 0; i < THREADS; i++) {
    pthread_join(th_c[i], NULL);
  }
  free(th_p);
  free(th_c);
  return 0;
}
