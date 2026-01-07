/*This program demonstrate the use of fsync. When I write operation is requested, file system first store the data in
 * the memory buffer, and then writes it to the disk in some time interval. If the data is needed to be written to the
 * disk immediately after the write call then fsync can be used. It is used in scenarios where immediate write
 * matters.*/

#include <assert.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main(void) {
  int fd = open("foo", O_CREAT | O_WRONLY | O_TRUNC, 0644);
  assert(fd > -1);
  char *buf = "hello world... what's going on here and there yoo??....dope shit";
  int c = write(fd, buf, strlen(buf));
  assert(c == strlen(buf));
  c = fsync(fd);
  assert(c == 0);
  printf("done!");
}
