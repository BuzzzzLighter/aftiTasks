#pragma once
#include <stdlib.h>

void bubbleSort(void* array, size_t count, size_t size, int (*compare)(void*, void*));