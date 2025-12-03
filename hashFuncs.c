#include "hashFuncs.h"
#include <string.h>
#include <math.h>
#define EPSILON 1e-9

int compareInt(void *a, void *b) {
    int x = *(int *)a;
    int y = *(int *)b;
    return (x > y) - (x < y);
}

int compareChar(void *a, void *b) {
    char x = *(char *)a;
    char y = *(char *)b;
    return (x > y) - (x < y);
}

int compareDouble(void *a, void *b) {
    double diff = *(double *)a - *(double *)b;
    if (fabs(diff) < EPSILON) return 0;
    return (diff > 0) - (diff < 0);
}

int compareString(void *a, void *b) {
    return strcmp((char *)a, (char *)b);
}

unsigned long hashInt(void *key) {
    int value = *(int *)key;
    return (unsigned long)(value * 2654435761u); //специльная константа для получения кэша далекокого друг от друга 
}

unsigned long hashChar(void *key) {
    unsigned char c = *(unsigned char *)key;
    return (unsigned long)c;
}

unsigned long hashDouble(void *key) {
    double val = *(double *)key;
    unsigned long long hash;
    memcpy(&hash, &val, sizeof(double));
    return hash * 11400714819323198485llu;
}

unsigned long hashString(void *key) {
    unsigned char *str = (unsigned char *)key;
    unsigned long hash = 5381; 
    int c;
    while ((c = *str++))
        hash = hash * 33 + c; 
    return hash;
}

