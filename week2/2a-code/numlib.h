#include <stdint.h>
#include <stdio.h>

void skipspaces(FILE *f);

// Read unsigned integer in base-10 ASCII format from the given file.
// Stores the resulting number in the location pointed to by 'out'.
// Stops at the first non-digit character, which is left unread. Returns nonzero
// on failure. Fails if no digits are read before a non-digit is encountered.
// Returns EOF if the first character read results in EOF.
int read_uint_ascii(FILE *f, uint32_t *out);

int read_double_bin(FILE *f, double *out);

int read_double_ascii(FILE *f, double *out);

int write_double_bin(FILE *f, double x);
