#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main(void) {
  // close(STDOUT_FILENO);
  freopen("test", "w", stdout);
  printf("hello world\n");
  return 0;
}
