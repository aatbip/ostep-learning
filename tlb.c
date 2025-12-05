#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define PAGESIZE 4096
#define MAX_PAGES 1000
#define ITERATIONS 100000000 // Adjust to run for a few seconds

int main() {
  int *a;
  int jump = PAGESIZE / sizeof(int); // 1024 integers per 4KB page
  struct timespec start, end;
  double time_taken, avg_access_time;

  // Test for different numbers of pages
  for (int numpages = 1; numpages <= MAX_PAGES; numpages += 10) {
    // Allocate array to span numpages pages
    a = (int *)malloc(numpages * PAGESIZE);
    if (!a) {
      printf("Allocation failed for %d pages\n", numpages);
      continue;
    }

    // Warm up the array to ensure pages are mapped
    for (int i = 0; i < numpages * jump; i += jump) {
      a[i] = 0;
    }

    // Time the loop
    clock_gettime(CLOCK_MONOTONIC, &start);
    for (long k = 0; k < ITERATIONS; k++) {
      for (int i = 0; i < numpages * jump; i += jump) {
        a[i] += 1;
      }
    }
    clock_gettime(CLOCK_MONOTONIC, &end);

    // Calculate average access time (in nanoseconds)
    time_taken =
        (end.tv_sec - start.tv_sec) * 1e9 + (end.tv_nsec - start.tv_nsec);
    avg_access_time = time_taken / (numpages * ITERATIONS);

    printf("NUMPAGES=%d, Avg Access Time=%.2f ns\n", numpages, avg_access_time);

    free(a);
  }
  return 0;
}
