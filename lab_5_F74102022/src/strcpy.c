#include "../include/strcpy.h"

char *sstrcpy(char *dest, const char *src) 
{	
  const char *p;
  char *q; 
  for(p = src, q = dest; *p != '\0'; p++, q++)
    *q = *p;
  *q = '\0';
  return dest;
}