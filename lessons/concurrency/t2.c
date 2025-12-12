#include <stdio.h>
char CompareAndSwap(int *ptr, int old, int new) {
  unsigned char ret;
  // Note that sete sets a ’byte’ not the word
  __asm__ __volatile__(" lock\n"
                       " cmpxchgl %2,%1\n"
                       " sete %0\n"
                       : "=q"(ret), "=m"(*ptr)
                       : "r"(new), "m"(*ptr), "a"(old)
                       : "memory");
  return ret;
}

int main(void) {
  int i = 45;
  unsigned char ret = CompareAndSwap(&i, 45, 56);
  printf("ret = %d, i = %d\n", ret, i); // ret is 0 or 1

  return 0;
}
