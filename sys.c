#include <sys/syscall.h> // for SYS_write
#include <unistd.h>

// Direct syscall: write(fd, buf, count)
long my_write(int fd, const void *buf, size_t count) {
  long ret;
  asm volatile("syscall"
               : "=a"(ret)              // output: return value in rax
               : "a"(SYS_write),        // input: syscall number in rax
                 "D"(fd),               // rdi = fd
                 "S"(buf),              // rsi = buf
                 "d"(count)             // rdx = count
               : "rcx", "r11", "memory" // clobbered registers
  );
  return ret;
}

int main() {
  my_write(1, "Hello raw syscall!\n", 20);
  return 0;
}
