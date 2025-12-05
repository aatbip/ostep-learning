#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  printf("hello world (pid:%d)\n", (int)getpid());
  int rc = fork();
  if (rc < 0) {
    // fork failed; exit
    fprintf(stderr, "fork failed\n");
    exit(1);
  } else if (rc == 0) {
    // child (new process)
    printf("hello, I am child (pid:%d)\n", (int)getpid());
    char **args = malloc(sizeof(char *) * 3);
    *args = strdup("wc");
    *(args + 1) = strdup("p1.c");
    *(args + 2) = NULL;
    execvp(*args, args);
    printf("this shouldn't print out\n");
  } else {
    int wc = wait(NULL);
    // parent goes down this path (original process)
    printf("hello, I am parent of %d (pid:%d)\n", rc, (int)getpid());
  }
  return 0;
}
