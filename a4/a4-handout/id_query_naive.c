#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <stdint.h>
#include <errno.h>
#include <assert.h>

#include "record.h"
#include "id_query.h"

struct naive_data {
  struct record *rs;
  int n;
};

struct naive_data* mk_naive(struct record* rs, int n) {
  struct naive_data *n_data = malloc(sizeof(struct naive_data));
  assert(n_data != NULL);
  n_data->rs = rs; // binds method of class (struct)
  n_data->n = n;
  return n_data;
}

void free_naive(struct naive_data* data) {
  assert(data != NULL);
  free(data);
  data = NULL; // in case our pointer holds memory that has been freed.
}

const struct record* lookup_naive(struct naive_data *data, int64_t needle) {
  int i = 0;
  int len = data->n; // stopping point
  struct record* points = data->rs; // so we can index into each row

  while (i < len) {
    assert(points != NULL);
    if (points[i].osm_id == needle) { // if id of current row == needle's id
      return &points[i];
    }
    i++;
  }
  assert(0 && "Record not found"); // shouldn't be reached, so assertion always fails
  return NULL;
}

int main(int argc, char** argv) {
  return id_query_loop(argc, argv,
                    (mk_index_fn)mk_naive,
                    (free_index_fn)free_naive,
                    (lookup_fn)lookup_naive);
}
