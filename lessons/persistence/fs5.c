/*This program creates hard links for a file and checks for the number of links before unlinking them. */
#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>

int main(void) {
  int ch = mkdir("links-test", 0777);
  if (ch == -1) {
    perror("mkdir");
  }
  ch = open("links-test/file0", O_CREAT | O_WRONLY);
  if (ch == -1) {
    perror("open");
  }
  int i = 1;
  while (i <= 5) {
    char n[256];
    snprintf(n, sizeof(n), "links-test/file%d", i);
    ch = link("links-test/file0", n);
    if (ch == -1) {
      perror("link");
    }
    i++;
  }
  struct stat st;
  stat("links-test/file0", &st);
  printf("link count: %ld\n", st.st_nlink);
}
