#ifndef DEQUE_H
#define DEQUE_H

#include <string.h>
#include <stdbool.h>

typedef struct {
    void *data;
    size_t front;
    size_t capacity;
    size_t back;
    size_t size;
    size_t elementSize;
} Deque;

void deque_resize(Deque *deque, size_t newCapacity);
void deque_init(Deque *deque, size_t capacity, size_t element_size);
void deque_push_back(Deque *deque, void *element);
void deque_push_front(Deque *deque, void *element);
void deque_pop_back(Deque *deque, void *out);
void deque_pop_front(Deque *deque, void *out);
void deque_get(Deque *deque, size_t index, void *out);
size_t deque_size(Deque *deque);
bool deque_empty(Deque *deque);
void deque_free(Deque *deque);

#endif