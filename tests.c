#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include "hashFuncs.h"
#include "hashTable.h"


void NextIndexTest() {
    size_t capacity = 5;
    assert(next_index(0, capacity) == 1);
    assert(next_index(4, capacity) == 0);
}

void hashT_create_test() {
    HashTable *ht = hashT_create(4, hashString, compareString, free, free);
    assert(ht != NULL);
    assert(ht->capacity == 4);
    assert(ht->size == 0);
    hashT_destroy(ht);
}

void hashT_insert_search_test() {
    HashTable *ht = hashT_create(4, hashString, compareString, free, free);
    assert(hashT_insert(ht, strdup("apple"), strdup("green")) == 1);
    assert(hashT_insert(ht, strdup("banana"), strdup("yellow")) == 1);
    assert(hashT_insert(ht, strdup("cherry"), strdup("red")) == 1);

    char *v = hashT_search(ht, "apple");
    assert(v && strcmp(v, "green") == 0);
    v = hashT_search(ht, "banana");
    assert(v && strcmp(v, "yellow") == 0);
    v = hashT_search(ht, "cherry");
    assert(v && strcmp(v, "red") == 0);

    hashT_destroy(ht);
}

void hashT_remove_test() {
    HashTable *ht = hashT_create(4, hashString, compareString, free, free);
    hashT_insert(ht, strdup("apple"), strdup("green"));
    hashT_insert(ht, strdup("banana"), strdup("yellow"));
    hashT_insert(ht, strdup("cherry"), strdup("red"));

    assert(hashT_remove(ht, "banana") == 1);
    assert(hashT_search(ht, "banana") == NULL);
    assert(ht->size == 2);

    assert(hashT_remove(ht, "apple") == 1);
    assert(hashT_remove(ht, "cherry") == 1);
    assert(ht->size == 0);

    hashT_destroy(ht);
}

int foreach_counter = 0;
void count_func(void *key, void *value) {
    (void)key;
    (void)value;
    foreach_counter++;
}

void hashT_foreach_test() {
    HashTable *ht = hashT_create(4, hashString, compareString, free, free);
    hashT_insert(ht, strdup("apple"), strdup("green"));
    hashT_insert(ht, strdup("banana"), strdup("yellow"));
    hashT_insert(ht, strdup("cherry"), strdup("red"));

    hashT_foreach(ht, count_func);
    assert(foreach_counter == 3);

    hashT_destroy(ht);
}

void hashT_resize_test() {
    HashTable *ht = hashT_create(4, hashString, compareString, free, free);
    hashT_insert(ht, strdup("apple"), strdup("green"));
    hashT_insert(ht, strdup("banana"), strdup("yellow"));

    size_t old_cap = ht->capacity;
    assert(hashT_resize(ht, old_cap * 2) == 1);
    assert(ht->capacity == old_cap * 2);

    char *v = hashT_search(ht, "apple");
    assert(v && strcmp(v, "green") == 0);
    v = hashT_search(ht, "banana");
    assert(v && strcmp(v, "yellow") == 0);

    hashT_destroy(ht);
}


void runAllTests() {
    NextIndexTest();
    hashT_create_test();
    hashT_insert_search_test();
    hashT_remove_test();
    hashT_foreach_test();
    hashT_resize_test();
    printf("PABEDA");
}