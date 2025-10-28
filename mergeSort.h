#pragma once

void merge(void *arr, size_t left, size_t mid, size_t right, size_t size, int (*compare)(void *, void *));
void mergeSort(void *arr, size_t left, size_t right, size_t size, int (*compare)(void *, void *));//