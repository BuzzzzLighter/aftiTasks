#include "swap.h"
#include <stdio.h>
#include <string.h>

void swap(void *a, void *b, size_t size) {
    void *temp = malloc(size);
    if (temp == NULL) {
        printf("Ошибка выделения памяти\n");
        return;
    }
    memcpy(temp, a, size);
    memcpy(a, b, size);
    memcpy(b, temp, size);        
    free(temp);
}