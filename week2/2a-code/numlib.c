#include "numlib.h"
#include <stdint.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

void skipspaces(FILE *f)
{
  while (1)
  {
    int c = fgetc(f);
    if (!isspace(c))
    {
      if (c != EOF)
      {
        ungetc(c, f);
      }
      return;
    }
  }
}