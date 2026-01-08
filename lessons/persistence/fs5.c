/*This program creates hard links for a file and checks for the number of links before unlinking them. */
#include <dirent.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

int main(void) {
  DIR *dp = opendir("."); // open the current dir
  struct dirent *dir;
  while ((dir = readdir(dp)) != NULL) {
    if (strcmp(dir->d_name, "links-test") == 0) {
      printf("links-test exist. deleting...\n");
      DIR *dp = opendir("links-test");
      int i = 0;
      while ((readdir(dp)) != NULL) {
        char n[256];
        snprintf(n, sizeof(n), "links-test/file%d", i);
        unlink(n);
        i++;
      }
      closedir(dp);
      rmdir("links-test");
      break;
    }
  }

  if ((mkdir("links-test", 0777)) == -1) {
    perror("mkdir");
  }
  if ((open("links-test/file0", O_CREAT | O_WRONLY, 0777)) == -1) {
    perror("open");
  }
  int i = 1;
  while (i <= 5) {
    char n[256];
    snprintf(n, sizeof(n), "links-test/file%d", i);
    if ((link("links-test/file0", n)) == -1) {
      perror("link");
    }
    i++;
  }
  struct stat st;
  if ((stat("links-test/file0", &st)) == -1) {
    perror("stat");
  };
  printf("link count: %ld\n", st.st_nlink);
  closedir(dp);
}
