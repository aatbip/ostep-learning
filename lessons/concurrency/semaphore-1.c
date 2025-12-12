/* Using semaphore as a conditional variable -
 * We can use semaphore as a conditional variable. The initialization
 * parameter X should be 0 to make semaphore work as CV. In the program
 * below we are implementing a waiting mechanism in the parent to make
 * sure the child runs using semaphore. Note that we don't need a
 * separate conditional variable like in the case of CV (see cv2.c)
 * because semaphore itself stores the state X and manipulates it
 * internally.*/

#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct __arg {
  sem_t *s;
} arg_t;

void *child(void *arg) {
  sem_t *s = ((arg_t *)arg)->s;
  printf("I am child!\n");
  sem_post(s);
  return NULL;
}

int main(void) {
  printf("start\n");
  pthread_t th;
  sem_t s;
  arg_t *arg = malloc(sizeof(*arg));
  arg->s = &s;
  /* Initializing sem_init with the initial value of semaphore X as 0 to
   * make it work as CV.*/
  sem_init(&s, 0, 0);
  pthread_create(&th, NULL, child, (void *)arg);
  /* The below function sem_wait makes this "parent" thread to wait and
   * runs the child thread. This replaces pthread_mutex_join using semaphore.*/
  sem_wait(&s);
  free(arg);
  printf("end\n");
  return 0;
}
