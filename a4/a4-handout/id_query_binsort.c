#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <stdint.h>
#include <errno.h>
#include <assert.h>

#include "record.h"
#include "id_query.h"

struct bin_data {
  struct record *rs;
  int n;
};

/*
TODO: (in this order)
+   Make comparison function so we can use qsort()
+   Comparison func for bsearch?
+   Lookup func by using osm_id and bsearch as method
*/ 

int compare_func(const void *a, const void *b) {
  const struct record *record_a = (const struct record *)a;
  const struct record *record_b = (const struct record *)b;
  
  return record_a->osm_id - record_b->osm_id;
}

struct bin_data* mk_naive(struct record* rs, int n) {
  struct bin_data *n_data = malloc(sizeof(struct bin_data));
  assert(n_data != NULL);
  n_data->rs = rs; // binds method of class (struct)
  n_data->n = n;

  qsort(rs, n, sizeof(struct record), compare_func);
  return n_data;
}

void free_naive(struct bin_data* data) {
  assert(data != NULL);
  free(data);
  data = NULL; // in case our pointer holds memory that has been freed.
}

const struct record* lookup_binsort(struct bin_data *data, int64_t needle) {
  assert(data != NULL);
  assert(data->rs != NULL);
  
  struct record key;
  key.osm_id = needle;
  
  struct record *result = bsearch(&key, data->rs, data->n, sizeof(struct record), compare_func);
  
  if (result == NULL) {
    assert(0 && "Record not found");
  }
  
  return result;
}

int main(int argc, char** argv) {
  return id_query_loop(argc, argv,
                    (mk_index_fn)mk_naive,
                    (free_index_fn)free_naive,
                    (lookup_fn)lookup_binsort);
}
