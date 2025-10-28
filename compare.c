#include <stdio.h>
#include <string.h>
#define epsilon 1e-9

int compareInt(void *a, void *b) { 
    return *(int *)a - *(int *)b; 
}

int compareChar(void *a, void *b) { 
    return *(char *)a - *(char *)b;
}

int compareDouble(void *a, void *b) {    
    if (fabs(*(double*)a - *(double*)b) < epsilon)
        return 0;
    else if (*(double*)a - *(double*)b < 0)
        return -1;
    else
        return 1;
}

int compareString(void *a, void *b) { 
    return strcmp(*(char **)a, *(char **)b); 
}

