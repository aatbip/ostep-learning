/*This program creates hard links for a file and checks for the number of links before unlinking them. */
#include <stdio.h>
#include <sys/stat.h>

int main(void) {
  int ch = mkdir("links-test", 0777);
  if (ch != 0) {
    perror("mkdir");
  }
}
