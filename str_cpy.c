#include <stdlib.h>
#include "str_len.h"

char *str_cpy(char * str)
{
  char *cpy = NULL;
  int length = str_len(str);
  cpy = malloc(length * sizeof(char));

  int i = 0;

  while(str[i] != '\0')
  {
    cpy[i] = str[i];
    i = i + 1;
  }

  return(cpy);
}