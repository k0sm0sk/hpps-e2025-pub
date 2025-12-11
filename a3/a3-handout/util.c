#include "util.h"
#include <math.h>
#include <stdio.h>
#include <assert.h>

double distance(int d, const double *x, const double *y) {
  double sum = 0.0;
  for (int i = 0; i < d; i++) {
    double diff = x[i] - y[i];
    sum += diff * diff;
  }
  return sqrt(sum);
}

int insert_if_closer(int k, int d,
                     const double *points, int *closest, const double *query,
                     int candidate) {
  double candidate_dist = distance(d, points + candidate * d, query);
  
  int insert_pos = -1;
  for (int i = 0; i < k; i++) {
    if (closest[i] == -1) {
      insert_pos = i;
      break;
    }
    
    double existing_dist = distance(d, points + closest[i] * d, query);
    if (candidate_dist < existing_dist) {
      insert_pos = i;
      break;
    }
  }
  
  if (insert_pos == -1) {
    return 0;
  }
  
  for (int i = k - 1; i > insert_pos; i--) {
    closest[i] = closest[i - 1];
  }
  
  closest[insert_pos] = candidate;
  return 1;
}
