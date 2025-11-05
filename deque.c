#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "deque.h"


void deque_resize(Deque *deque, size_t newCapacity) {
    if (newCapacity == 0) { 
        newCapacity = 1;
    }

    void *newData = malloc(newCapacity * deque->elementSize);
    if (newData == NULL) {
        printf("Error allocating memory\n");
        return;
    }

    if (deque->size > 0){
        if (deque->front < deque->back) {
            memcpy(newData,(char*)deque->data + deque->front * deque->elementSize, deque->size * deque->elementSize);
        } 
        else {
            size_t firstPart = (deque->capacity - deque->front) * deque->elementSize;
            size_t secondPart = deque->back * deque->elementSize;

            memcpy(newData,(char*)deque->data + deque->front * deque->elementSize, firstPart);
            memcpy((char*)newData + firstPart, deque->data, secondPart);
        }
    }

    free(deque->data);
    deque->data = newData;
    deque->capacity = newCapacity;
    deque->front = 0;
    deque->back = deque->size;
}

void deque_init(Deque *deque, size_t capacity, size_t element_size){
    if (capacity == 0){
        capacity = 1;
    }
    deque->elementSize = element_size;
    deque->data = malloc(capacity * deque->elementSize);
    deque->front = 0;
    deque->capacity = capacity;
    deque->back = 0;
    deque->size = 0;
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
    deque->front = (deque->front - 1 + deque->capacity) % deque->capacity;
    memcpy((char*)deque->data + deque->front * deque->elementSize, element, deque->elementSize);
    deque->size++;
}

void deque_pop_back(Deque *deque, void *out){
    if (deque->size == 0){
        printf("Deque is already empty\n");
        return;
    }
    deque->back = (deque->back - 1 + deque->capacity) % deque->capacity;
    memcpy(out, (char*)deque->data + deque->back * deque->elementSize, deque->elementSize);
    deque->size--;
}

void deque_pop_front(Deque *deque, void *out){
    if (deque->size == 0){
        printf("Deque is already empty\n");
        return;
    }
    memcpy(out, (char*)deque->data + deque->front * deque->elementSize, deque->elementSize);
    deque->front = (deque->front + 1) % deque->capacity;
    deque->size--;
}

void deque_get(Deque *deque, size_t index, void *out){
    if (index >= deque->size){
        printf("Index out of range\n");
        return;
    }

    size_t real_index = (deque->front + index) % deque->capacity;
    memcpy(out, (char*)deque->data + real_index * deque->elementSize, deque->elementSize);
}

bool deque_empty(Deque *deque){
    return deque->size == 0;
}

size_t deque_size(Deque *deque){
    return deque->size;
}