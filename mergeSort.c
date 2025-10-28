#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void merge(void *arr, size_t left, size_t mid, size_t right, size_t size, int (*compare)(void *, void *)) {
    size_t n1 = mid - left + 1; 
    size_t n2 = right - mid;

    void *leftArr = malloc(size * n1);
    void *rightArr = malloc(size * n2);

    if (leftArr == NULL || rightArr == NULL) {
        printf("Memory allocation failed\n");
        return;
    }
//
    char *array = (char*)arr;

    memcpy(leftArr, array + left * size, n1 * size);
    memcpy(rightArr, array + (mid + 1) * size, n2 * size);

    size_t i = 0, j = 0, k = left;

    char *l = (char*)leftArr;
    char *r = (char*)rightArr;
//
    while (i < n1 && j < n2) {
        if (compare(l + i * size, r + j * size) <= 0) {
            memcpy(array + k * size, l + i * size, size);
            i++;
        } else {
            memcpy(array + k * size, r + j * size, size);
            j++;
        }
        k++;
    }
//
    while (i < n1) {
        memcpy(array + k * size, l + i * size, size);
        i++;
        k++;
    }

    while (j < n2) {
        memcpy(array + k * size, r + j * size, size);
        j++;
        k++;
    }
//
    free(leftArr);
    free(rightArr);
}

void mergeSort(void *arr, size_t left, size_t right, size_t size, int (*compare)(void *, void *)) {
    if (left < right) {
        size_t mid = left + (right - left) / 2;
        mergeSort(arr, left, mid, size, compare);
        mergeSort(arr, mid + 1, right, size, compare);
        merge(arr, left, mid, right, size, compare);
    }
}