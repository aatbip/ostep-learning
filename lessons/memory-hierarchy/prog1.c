#include <stdint.h>
#include <stdio.h>

int main(void) {
  int s = 3, b = 6;
  uint64_t addr = 0x1A3F5048;

  int offset = addr & ((1 << b) - 1); // low b bits

  return 0;
}
