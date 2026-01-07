/* This program demonstrates the use of lseek() to move the file offset.
 * Here, the offset is set to 6 and the whence parameter is SEEK_CUR,
 * meaning the file offset is advanced 6 bytes **from its current position**.
 * The subsequent read() will start from this new position,
 * effectively skipping the first 6 bytes of the file.*/

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main(void) {
  int fd = open("foo1", O_RDONLY);
  if (fd == -1) {
    perror("open");
  }
  char *buf = malloc(50);
  lseek(fd, 6, SEEK_CUR);
  int r = read(fd, buf, 50);
  if (r == -1) {
    perror("read");
  }
  printf("buf: %s\n", buf);
  free(buf);
}
