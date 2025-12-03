#ifndef HASH_TABLE_H
#define HASH_TABLE_H
#include <stddef.h>
#include <stdbool.h> 


typedef struct {
    void *key;
    void *value;
    bool is_occupied;
    bool is_deleted;
} HashCell;

typedef struct {
    HashCell *entries; //указатель на массив ячеек HashCell
    size_t capacity;
    size_t size;

    unsigned long (*hash_func)(void *key);
    int (*cmp_func)(void *a, void *b);
    void (*free_key)(void *key);
    void (*free_value)(void *value);
} HashTable;

HashTable *hashT_create(size_t capacity, unsigned long (*hash_func)(void *),int (*cmp_func)(void *, void *),
                    void (*free_key)(void *), void (*free_value)(void *));

void hashT_destroy(HashTable *hashTab);

void hashT_insert(HashTable *hashTab, void *key, void *value);//заменить int
void *hashT_search(HashTable *hashTab,  void *key);
void hashT_remove(HashTable *hashTab, void *key);//int заменить 

size_t next_index(size_t i, size_t capacity);

void hashT_foreach(HashTable *hashTab, void (*func)(void *key, void *value));
void hashT_resize(HashTable *hashTab, size_t new_capacity); //заменить int
void printPairs(void* key, void* value);

#endif 
