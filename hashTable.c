#include <stdlib.h>
#include <stdio.h>
#include "hashTable.h"

size_t next_index(size_t i, size_t capacity) {
    return (i + 1) % capacity;
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
        if (hashTab->entries[i].is_occupied && !hashTab->entries->is_deleted){
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

int hashT_insert(HashTable *hashTab, void *key, void *value){
    if (!hashTab) return 0;
    if ((double)hashTab->size / hashTab->capacity > 0.8){
        hashT_resize(hashTab, hashTab->capacity * 2);
    }
    
    unsigned long hash = hashTab->hash_func(key);
    size_t index = hash % hashTab->capacity;

    while (hashTab->entries[index].is_occupied && !hashTab->entries[index].is_deleted){
        if (hashTab->cmp_func(hashTab->entries[index].key, key) == 0){
            if (hashTab->free_value){
                hashTab->free_value(hashTab->entries[index].value);
            }
            hashTab->entries[index].value = value;
            return 1;
        }
        index = next_index(index, hashTab->capacity);
    }
    hashTab->entries[index].is_deleted = 0;
    hashTab->entries[index].is_occupied = 1;
    hashTab->entries[index].key = key;
    hashTab->entries[index].value = value;
    hashTab->size++;
    return 1;
}

void *hashT_search(HashTable *hashTab,  void *key){
    if (!hashTab) return NULL;

    unsigned long hash = hashTab->hash_func(key);
    size_t index = hash % hashTab->capacity;
    size_t start = index;

    while (hashTab->entries[index].is_occupied){
        if (hashTab->cmp_func(hashTab->entries[index].key, key) == 0){
            return hashTab->entries[index].value;
        }
        index = next_index(index, hashTab->capacity);
        if (index == start){ //сделали круг
            break; 
        }
    }
    return NULL;
}

int hashT_remove(HashTable *hashTab, void *key){
    if (!hashTab) return 0;
    unsigned long hash = hashTab->hash_func(key);
    size_t index = hash % hashTab->capacity;
    size_t start = index;

    while (hashTab->entries[index].is_occupied){
        if (!hashTab->entries[index].is_deleted && hashTab->cmp_func(hashTab->entries[index].key, key) == 0){
            if (hashTab->free_key) hashTab->free_key(hashTab->entries[index].key);
            if (hashTab->free_value) hashTab->free_value(hashTab->entries[index].value);
            hashTab->entries[index].is_deleted = 1;
            hashTab->size--;
            return 1;
        }
        index = next_index(index, hashTab->capacity);
        if (index == start){ //сделали круг
            break; 
        }
    }
    return 0;
}

void hashT_foreach(HashTable *hashTab, void (*func)(void *key, void *value)){
    if (!hashTab) return;
    for (int i = 0; i < hashTab->capacity; i++){
        if (hashTab->entries[i].is_occupied && !hashTab->entries[i].is_deleted){
            func(hashTab->entries[i].key, hashTab->entries[i].value);
        }
    }
}

int hashT_resize(HashTable *hashTab, size_t new_capacity){
    if (!hashTab) return 0;
    HashTable *new_hashTab = hashT_create(new_capacity, hashTab->hash_func, hashTab->cmp_func, hashTab->free_key, hashTab->free_value);
    if (!new_hashTab) return 0;
    for (int i = 0; i < hashTab->capacity; i++){
        if (hashTab->entries[i].is_occupied && !hashTab->entries[i].is_deleted){
            hashT_insert(new_hashTab, hashTab->entries[i].key, hashTab->entries[i].value);
        }
    }
    free (hashTab->entries);
    hashTab->entries = new_hashTab->entries;
    hashTab->capacity = new_hashTab->capacity;
    hashTab->size = new_hashTab->size;
    free(new_hashTab);
    return 1;
}

void printPairs(void* key, void* value){
    printf("%s ----> %s\n", key, value);
}