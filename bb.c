#include <linux/futex.h>

#include <stdio.h>
int main(void) {
  int a = 21;

  printf("%p\n", &a);

  return 0;
}
