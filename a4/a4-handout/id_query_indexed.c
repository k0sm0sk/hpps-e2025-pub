#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <stdint.h>
#include <errno.h>
#include <assert.h>

#include "record.h"
#include "id_query.h"



struct index_record {
    int64_t osm_id;
    const struct record *record;
};

struct indexed_data {
    struct index_record *irs;
    int n;
};

struct indexed_data * mk_indexed(struct record *rs, int n) {
    struct indexed_data *idx_data = malloc(sizeof(struct indexed_data));
    assert(idx_data != NULL);

    // I don't care who the IRS sends, I am not paying taxes
    idx_data->irs = malloc(n * sizeof(struct index_record)); //joke aside, indexed_data is array, so we need n times memory for the singular index_record 
    assert(idx_data->irs != NULL);

    idx_data->n = n;

    for (int i = 0; i < n; i++) {
        idx_data->irs[i].osm_id = rs[i].osm_id;
    }

    return idx_data;
    // ? Maybe we should add freeing of memory?
}

void free_indexed(struct indexed_data *data) {
    assert(data != NULL);
    free(data->irs); //frees irs array memory
    free(data); //frees memory for indexed_data struct itself
}

const struct record * lookup_indexed(struct indexed_data *data, int64_t needle) {
    // made checks here instead of in loop (from naive version)
    assert(data != NULL);
    assert(data->irs != NULL);

    int i = 0;
    int len = data->n; // stopping point
    struct index_record *points = data->irs;

    while (i < len) {
        if (points[i].osm_id == needle) { // if id of current row == needle's id
            return &points[i];
        }
        i++;
    }
    assert(0 && "Record not found"); // shouldn't be reached, so assertion always fails
    return NULL;
}

int main(int argc, char **argv)
{
    assert(argc >= 2 && "Incorrect arg amount");

    return id_query_loop(argc, argv,
                         (mk_index_fn)mk_indexed,
                         (free_index_fn)free_indexed,
                         (lookup_fn)lookup_indexed);
}
