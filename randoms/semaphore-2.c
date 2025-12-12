/* Here we solve the producer/consumer (bounded buffer) problem using semaphore.
 * This program creates a producer/consumer buffer using semaphore.*/
#include <pthread.h>
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
  sem_wait(&p);
  sem_wait(&mutex); // add lock
  put(rand());
  sem_post(&mutex);
  sem_post(&c);
  return NULL;
}

void *consumer(void *arg) {
  sem_wait(&c);
  sem_wait(&mutex); // add lock
  int tmp = get();
  printf("consumed: %d\n", tmp);
  sem_post(&mutex);
  sem_post(&p);
  return NULL;
}

int main(void) {
  sem_init(&p, 0, MAX);
  sem_init(&c, 0, 0);
  sem_init(&mutex, 0, 1);
  pthread_t *th_p = malloc(sizeof(*th_p) * 10);
  pthread_t *th_c = malloc(sizeof(*th_p) * 10);
  for (int i = 0; i < 10; i++) {
    pthread_create(&th_p[i], NULL, producer, NULL);
  }
  for (int i = 0; i < 10; i++) {
    pthread_create(&th_c[i], NULL, consumer, NULL);
  }
  for (int i = 0; i < 10; i++) {
    pthread_join(th_p[i], NULL);
  }
  for (int i = 0; i < 10; i++) {
    pthread_join(th_c[i], NULL);
  }
  return 0;
}
