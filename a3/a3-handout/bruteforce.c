#include "bruteforce.h"
#include "util.h"
#include <stdlib.h>
#include <assert.h>

int* knn(int k, int d, int n, const double *points, const double* query) {
  assert(k > 0);
  assert(d > 0);
  assert(n > 0);

  int *closest_memory = malloc(k*sizeof(int));
  if (!closest_memory) {
    return NULL;
  }

  for (int i = 0; i < k; i++) {
    closest_memory[i] = -1; // ensure intialized list consists of -1 so (not actual distances)
  }


  for(int candidate = 0; candidate < n; candidate++) {
    insert_if_closer(k, d, points, closest_memory, query, candidate);
  }
  
  return closest_memory;
}