/* This program uses `open`, `write`, and `read` syscalls. It also uses `lseek` to move the offset to beginning of the
 * file in order to use `read` again with the same file descriptor after the `write`.*/

#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main(void) {
  int fd = open("foo", O_CREAT | O_RDWR | O_TRUNC);
  int s = write(fd, "hello\n", 6);
  if (s == -1) {
    perror("write");
  }
  lseek(fd, 0, SEEK_SET); // move offset to beginning
  char buf[20];
  int p = read(fd, buf, 20);
  if (p == -1) {
    perror("read");
  }
  printf("s: %s\n", buf);
}
