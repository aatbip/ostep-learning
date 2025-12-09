#include <pthread.h>
#include <stdio.h>

int done = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t c = PTHREAD_COND_INITIALIZER;

void *child(void *arg) {
  printf("From child\n");
  pthread_mutex_lock(&mutex);
  done = 1;
  pthread_cond_signal(&c);
  pthread_mutex_unlock(&mutex);
  return NULL;
}

void th_join() {
  pthread_mutex_lock(&mutex);
  while (done == 0) {
    pthread_cond_wait(&c, &mutex);
  }
  pthread_mutex_unlock(&mutex);
}

int main(void) {
  printf("start\n");
  pthread_t th;
  pthread_create(&th, NULL, child, NULL);
  for (long i = 0; i < 20; i++)
    printf("i: %ld\n", i);
  th_join();
  printf("end\n");
  return 0;
}
