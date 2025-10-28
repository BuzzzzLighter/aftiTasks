#include "bubbleSort.h"
#include "swap.h"
#include <stdio.h>

void bubbleSort(void* array, size_t count, size_t size, int (*compare)(void*, void*)) {
    if (array == NULL || compare == NULL || count == 0 || size == 0) {
        return;
    }
    
    char* base = (char*)array;
    for (size_t i = 0; i < count - 1; i++) {
        int swapped = 0;
        
        for (size_t j = 0; j < count - i - 1; j++) {
            void* current = base + j * size;
            void* next = base + (j + 1) * size;
            
            if (compare(current, next) > 0) {
                swap(current, next, size);
                swapped = 1;
            }
        }
 
        if (!swapped) {
            break;
        }
    }
}

