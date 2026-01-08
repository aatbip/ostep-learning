#include <assert.h>
#include <dirent.h>
#include <stdio.h>

int main(void) {
  DIR *dp = opendir("mydir");
  assert(dp != NULL);
  struct dirent *d;
  d = readdir(dp);
  printf("name: %s\n", d->d_name);
  return 0;
}
