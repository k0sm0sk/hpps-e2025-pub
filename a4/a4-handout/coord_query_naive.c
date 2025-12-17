#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <stdint.h>
#include <errno.h>
#include <assert.h>

#include "record.h"
#include "coord_query.h"

struct naive_data {
  struct record *rs;
  int n;
};

static double dist2(double x1, double y1, double x2, double y2) {
  double dx = x1 - x2;
  double dy = y1 - y2;
  return dx*dx + dy*dy;
}

//kopi af daniels struct naive_data
struct naive_data* mk_naive(struct record* rs, int n) {
  struct naive_data *n_data = malloc(sizeof(struct naive_data));
  assert(n_data != NULL);
  n_data->rs = rs; // binds method of class (struct)
  n_data->n = n;
  return n_data;
}

void free_naive(struct naive_data* data) {
  free(data);
}

const struct record* lookup_naive(struct naive_data *data,
                                  double lon, double lat) {
  if (data->n == 0) return NULL;

  const struct record *best = &data->rs[0];

  double best_dist = dist2(lon, lat, best->lon, best->lat);

  for (int i = 1; i < data->n; i++){
    double d = dist2(lon, lat, data->rs[i].lon, data->rs[i].lat);
    if (d < best_dist) {
      best_dist = d;
      best = &data ->rs[i];
    }
  }

  return best;
}


int main(int argc, char** argv) {
  return coord_query_loop(argc, argv,
                          (mk_index_fn)mk_naive,
                          (free_index_fn)free_naive,
                          (lookup_fn)lookup_naive);
}
