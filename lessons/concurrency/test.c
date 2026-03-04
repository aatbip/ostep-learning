#include <pthread.h>
#include <stdio.h>

void *routine(void *arg) {
  for (int i = 0; i <= 50; i++) {
    printf("%d ", i);
    if (i == 50)
      printf("\n");
  }
  return NULL;
}

int main(void) {
  pthread_t th1, th2;
  pthread_create(&th1, NULL, routine, NULL);
  for (long i = 0; i < 10; i++)
    printf("i: %ld\n", i);

  // pthread_create(&th2, NULL, routine, NULL);
  // pthread_join(th1, NULL);
  // pthread_join(th2, NULL);
  return 0;
}
