#ifndef HASH_FUNCS_H
#define HASH_FUNCS_H
#include <string.h>

int compareInt(void *a, void *b);
int compareString(void *a, void *b);
int compareChar(void *a, void *b);
int compareDouble(void *a, void *b);
unsigned long hashInt(void *key);
unsigned long hashChar(void *key);
unsigned long hashDouble(void *key);
unsigned long hashString(void *key);
#endif