#include <stdlib.h>
#include <stdio.h>
#include "hashTable.h"

size_t next_index(size_t i, size_t capacity) {
    return (i + 1) % capacity;
}

static int is_active_cell(HashCell *cell) {
    return cell->is_occupied && !cell->is_deleted;
}

HashTable *hashT_create(size_t capacity, unsigned long (*hash_func)(void *),int (*cmp_func)(void *, void *), void (*free_key)(void *), void (*free_value)(void *)){
    HashTable *hashTable = malloc(sizeof (HashTable));
    if (!hashTable){
        printf("Memory allocation error\n");
        return NULL;
    }
    hashTable->entries = calloc(capacity, sizeof (HashCell));
    if (!hashTable->entries){
        printf("Memory allocation error\n");
        free(hashTable);
        return NULL;
    }
    hashTable->capacity = capacity;
    hashTable->size = 0;
    hashTable->hash_func = hash_func;
    hashTable->cmp_func = cmp_func;
    hashTable->free_key = free_key;
    hashTable->free_value = free_value;
    
    return hashTable;
}

void hashT_destroy(HashTable *hashTab){
    if(!hashTab) return;

    for (int i = 0; i < hashTab->capacity; i++){
        if (is_active_cell(&hashTab->entries[i])){
            if (hashTab->free_key){
                hashTab->free_key(hashTab->entries[i].key);
            }
            if (hashTab->free_value){
                hashTab->free_value(hashTab->entries[i].value);
            }
        }
    }

    free(hashTab->entries);
    free(hashTab);
}

void hashT_insert(HashTable *hashTab, void *key, void *value){
    if (!hashTab) return;
    if ((double)hashTab->size / hashTab->capacity > 0.8){
        hashT_resize(hashTab, hashTab->capacity * 2);
    }
    
    unsigned long hash = hashTab->hash_func(key);
    size_t index = hash % hashTab->capacity;

    while (is_active_cell(&hashTab->entries[index])){
        if (hashTab->cmp_func(hashTab->entries[index].key, key) == 0){
            if (hashTab->free_value){
                hashTab->free_value(hashTab->entries[index].value);
            }
            hashTab->entries[index].value = value;
            return;
        }
        index = next_index(index, hashTab->capacity);
    }
    hashTab->entries[index].is_deleted = 0;
    hashTab->entries[index].is_occupied = 1;
    hashTab->entries[index].key = key;
    hashTab->entries[index].value = value;
    hashTab->size++;
    return;
}

void *hashT_search(HashTable *hashTab, void *key) {
    if (!hashTab) return NULL;

    unsigned long hash = hashTab->hash_func(key);
    size_t index = hash % hashTab->capacity;
    size_t start = index;

    while (hashTab->entries[index].is_occupied) {

        if (!hashTab->entries[index].is_deleted &&
            hashTab->cmp_func(hashTab->entries[index].key, key) == 0)
        {
            return hashTab->entries[index].value;
        }

        index = next_index(index, hashTab->capacity);
        if (index == start)
            break;
    }

    return NULL;
}

void hashT_remove(HashTable *hashTab, void *key){
    if (!hashTab) return;
    unsigned long hash = hashTab->hash_func(key);
    size_t index = hash % hashTab->capacity;
    size_t start = index;

    while (hashTab->entries[index].is_occupied){
        if (!hashTab->entries[index].is_deleted && hashTab->cmp_func(hashTab->entries[index].key, key) == 0){
            if (hashTab->free_key) hashTab->free_key(hashTab->entries[index].key);
            if (hashTab->free_value) hashTab->free_value(hashTab->entries[index].value);
            hashTab->entries[index].is_deleted = 1;
            hashTab->size--;
            return;
        }
        index = next_index(index, hashTab->capacity);
        if (index == start){ //сделали круг
            break; 
        }
    }
    return;
}

void hashT_foreach(HashTable *hashTab, void (*func)(void *key, void *value)){
    if (!hashTab) return;
    for (int i = 0; i < hashTab->capacity; i++){
        if (is_active_cell(&hashTab->entries[i])){
            func(hashTab->entries[i].key, hashTab->entries[i].value);
        }
    }
}

void hashT_resize(HashTable *hashTab, size_t new_capacity) {
    if (!hashTab) return;

    HashCell *old_entries = hashTab->entries;
    size_t old_capacity = hashTab->capacity;

    HashCell *new_entries = calloc(new_capacity, sizeof(HashCell));
    if (!new_entries) {
        printf("Memory allocation error\n");
        return;
    }

    hashTab->entries = new_entries;
    hashTab->capacity = new_capacity;
    hashTab->size = 0; 

    for (size_t i = 0; i < old_capacity; i++) {
        if (is_active_cell(&old_entries[i])) {
            hashT_insert(hashTab, old_entries[i].key, old_entries[i].value);
        }
    }

    free(old_entries);
}


void printPairs(void* key, void* value){
    printf("%s ----> %s\n", key, value);
}

//в resize именно ресайзить:))))