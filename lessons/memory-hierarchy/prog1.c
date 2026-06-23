#include <stdint.h>
#include <stdio.h>

int main(void) {
  int s = 3, b = 6;
  uint64_t addr = 0x1A3F5048;

  int offset = addr & ((1 << b) - 1);         // low b bits
  int set_idx = (addr >> b) & ((1 << s) - 1); // next s bits
  int tag = addr >> (b + s);                  // remaining bits

  printf("offset=%d set=%d tag=%d\n", offset, set_idx, tag);
  return 0;
}
