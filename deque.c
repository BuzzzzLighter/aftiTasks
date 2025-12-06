#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include "deque.h"



void deque_init(Deque *deque, size_t capacity, size_t element_size){
    if (capacity == 0 || element_size == 0) return;
    deque->elementSize = element_size;
    deque->capacity = capacity;
    deque->data = malloc(capacity * deque->elementSize);
    if (deque->data == NULL){
        printf("Memory allocation failed");
        return;
    }
    deque->front = 0;
    deque->back = 0;
    deque->size = 0;
}

static void deque_resize(Deque *deque, size_t newCapacity) {
    if (newCapacity == deque->capacity) return;

    if (newCapacity == 0) {
        free(deque->data);
        deque->data = NULL;
        deque->capacity = 0;
        deque->front = 0;
        deque->back = 0;
        deque->size = 0;
        return;
    }

    if (newCapacity < deque->size) {
        deque->size = newCapacity;
    }

    void *newData = malloc(newCapacity * deque->elementSize);
    if (newData == NULL) {
        printf("Error allocating memory\n");
        return;
    }

    for (size_t i = 0; i < deque->size; ++i) {
        size_t oldIndex = (deque->front + i) % deque->capacity;
        memcpy((char*)newData + i * deque->elementSize,(char*)deque->data + oldIndex * deque->elementSize, deque->elementSize);
    }

    free(deque->data);
    deque->data = newData;
    deque->capacity = newCapacity;

    deque->front = 0;
    deque->back  = deque->size % newCapacity;
}


void deque_free(Deque *deque){
    free(deque->data);
    deque->data = NULL; 
    deque->front = 0;
    deque->capacity = 0;
    deque->back = 0;
    deque->size = 0;
}

void deque_push_back(Deque *deque, void *element){
    if (deque->size == deque->capacity){
        deque_resize(deque, deque->capacity * 2);
    }
    memcpy((char*)deque->data + deque->back * deque->elementSize, element, deque->elementSize);
    deque->back = (deque->back + 1) % deque->capacity;
    deque->size++;
}

void deque_push_front(Deque *deque, void *element){
    if (deque->size == deque->capacity){
        deque_resize(deque, deque->capacity * 2);
    }
    if (deque->front == 0) {
        deque->front = deque->capacity - 1;
    } else {
        deque->front--;
    }
    memcpy((char*)deque->data + deque->front * deque->elementSize, element, deque->elementSize);
    deque->size++;
}

void deque_pop_back(Deque *deque, void *out){
    if (deque->size == 0){
        return;
    }
    deque->back = (deque->back - 1 + deque->capacity) % deque->capacity;
    memcpy(out, (char*)deque->data + deque->back * deque->elementSize, deque->elementSize);
    deque->size--;
}

void deque_pop_front(Deque *deque, void *out){
    if (deque->size == 0){
        return;
    }
    memcpy(out, (char*)deque->data + deque->front * deque->elementSize, deque->elementSize);
    deque->front = (deque->front + 1) % deque->capacity;
    deque->size--;
}

bool deque_empty(Deque *deque){
    return deque->size == 0;
}

size_t deque_size(Deque *deque){
    return deque->size;
}

bool deque_peek_front(Deque *deque, void *out) {
    if (deque->size == 0) return false;
    memcpy(out, (char*)deque->data + deque->front * deque->elementSize, deque->elementSize);
    return true;
}

bool deque_peek_back(Deque *deque, void *out) {
    if (deque->size == 0) return false;
    size_t index = (deque->back == 0) ? deque->capacity - 1 : deque->back - 1;
    memcpy(out, (char*)deque->data + index * deque->elementSize, deque->elementSize);
    return true;
}
