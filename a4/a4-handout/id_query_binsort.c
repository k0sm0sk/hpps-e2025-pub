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

int compare_func();

struct bin_data* mk_naive(struct record* rs, int n) {
  struct bin_data *n_data = malloc(sizeof(struct bin_data));
  assert(n_data != NULL);
  n_data->rs = rs; // binds method of class (struct)
  n_data->n = n;

  // + uncomment when compare func is done
  //qsort(rs, n, sizeof(struct record), compare_func)
  return n_data;
}

void free_naive(struct bin_data* data) {
  assert(data != NULL);
  free(data);
  data = NULL; // in case our pointer holds memory that has been freed.
}