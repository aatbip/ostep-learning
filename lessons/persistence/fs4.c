#include <assert.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

int main(void) {
  mkdir("mydir", 0777);
  DIR *dp = opendir("mydir");
  struct dirent *d;
  while ((d = readdir(dp)) != NULL) {
    struct stat st;
    char path[1024];
    snprintf(path, sizeof(path), "mydir/%s", d->d_name);
    stat(path, &st);
    printf("(dirent)name: %s\n", d->d_name);
    printf("(st)inode: %ld\n", st.st_ino);
    printf("(dirent)inode: %ld\n", d->d_ino);
    rmdir(path);
  }
  rmdir("mydir");
  closedir(dp);
  return 0;
}
