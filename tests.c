#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include "hashFuncs.h"
#include "hashTable.h"


void hashT_auto_resize_test() { //проверяем сработает ли ресайз
    HashTable *ht = hashT_create(2, hashString, compareString, free, free);

    hashT_insert(ht, strdup("aaa"), strdup("1"));
    hashT_insert(ht, strdup("bbb"), strdup("2"));
    hashT_insert(ht, strdup("ccc"), strdup("3"));

    assert(strcmp(hashT_search(ht, "aaa"), "1") == 0);
    assert(strcmp(hashT_search(ht, "bbb"), "2") == 0);
    assert(strcmp(hashT_search(ht, "ccc"), "3") == 0);

    hashT_destroy(ht);
}

unsigned long badHash(void *key) { 
    (void) key;
    return 42;
}

void hashT_all_collisions_test() {
    HashTable *ht = hashT_create(8, badHash, compareString, free, free);

    const char *keys[] = {"a","b","c","d","e","f","g","h"};
    const char *vals[] = {"1","2","3","4","5","6","7","8"};

    for (int i = 0; i < 8; i++)
        hashT_insert(ht, strdup(keys[i]), strdup(vals[i]));

    for (int i = 0; i < 8; i++) {
        char *v = hashT_search(ht, (void*)keys[i]);
        assert(v && strcmp(v, vals[i]) == 0);
    }

    hashT_destroy(ht);
}

void hashT_delete_chain_middle_test() {
    HashTable *ht = hashT_create(8, badHash, compareString, free, free);

    hashT_insert(ht, strdup("a"), strdup("1"));
    hashT_insert(ht, strdup("b"), strdup("2"));
    hashT_insert(ht, strdup("c"), strdup("3"));

    hashT_remove(ht, "b");

    assert(strcmp(hashT_search(ht, "c"), "3") == 0);

    assert(hashT_search(ht, "b") == NULL);

    hashT_destroy(ht);
}

void hashT_reinsert_after_delete_test() {
    HashTable *ht = hashT_create(4, hashString, compareString, free, free);

    hashT_insert(ht, strdup("apple"), strdup("green"));
    hashT_insert(ht, strdup("banana"), strdup("yellow"));

    hashT_remove(ht, "banana");

    hashT_insert(ht, strdup("banana"), strdup("yellow2"));

    assert(strcmp(hashT_search(ht, "banana"), "yellow2") == 0);
    assert(ht->size == 2);

    hashT_destroy(ht);
}

void hashT_null_value_test() {
    HashTable *ht = hashT_create(4, hashString, compareString, free, NULL);

    hashT_insert(ht, strdup("a"), NULL);
    void *v = hashT_search(ht, "a");

    assert(v == NULL);

    hashT_destroy(ht);
}

void hashT_big_stress_test() {
    HashTable *ht = hashT_create(4, hashInt, compareInt, free, free);

    const int N = 1000;

    for (int i = 0; i < N; i++) {
        int *k = malloc(sizeof(int));
        int *v = malloc(sizeof(int));
        *k = i;
        *v = i + 100;
        hashT_insert(ht, k, v);
    }

    for (int i = 0; i < N; i++) {
        int key = i;
        int *v = hashT_search(ht, &key);
        assert(v && *v == i + 100);
    }

    hashT_destroy(ht);
}

int foreach_sum = 0;

void sum_func(void *key, void *value) {
    (void)key;
    foreach_sum += *(int*)value;
}

void hashT_foreach_after_delete_test() {
    HashTable *ht = hashT_create(8, hashInt, compareInt, free, free);

    for (int i = 1; i <= 5; i++) {
        int *k = malloc(sizeof(int));
        int *v = malloc(sizeof(int));
        *k = i;
        *v = i;
        hashT_insert(ht, k, v);
    }

    hashT_remove(ht, &(int){3});

    hashT_foreach(ht, sum_func);

    assert(foreach_sum == (1 + 2 + 4 + 5));

    hashT_destroy(ht);
}

void hashT_search_not_found_full_table_test() {
    HashTable *ht = hashT_create(4, badHash, compareString, free, free);

    hashT_insert(ht, strdup("a"), strdup("1"));
    hashT_insert(ht, strdup("b"), strdup("2"));
    hashT_insert(ht, strdup("c"), strdup("3"));

    assert(hashT_search(ht, "zzz") == NULL);

    hashT_destroy(ht);
}

void hashT_update_value_test() {
    HashTable *ht = hashT_create(4, hashString, compareString, free, free);

    hashT_insert(ht, strdup("k"), strdup("v1"));
    hashT_insert(ht, strdup("k"), strdup("v2"));

    assert(strcmp(hashT_search(ht, "k"), "v2") == 0);
    assert(ht->size == 1);

    hashT_destroy(ht);
}

void hashT_empty_destroy_test() {
    HashTable *ht = hashT_create(10, hashString, compareString, free, free);
    hashT_destroy(ht);
}

void hashT_search_wraparound_test() {
    HashTable *ht = hashT_create(4, badHash, compareString, free, free);

    hashT_insert(ht, strdup("a"), strdup("1"));
    hashT_insert(ht, strdup("b"), strdup("2"));
    hashT_insert(ht, strdup("c"), strdup("3"));

    assert(hashT_search(ht, "xxxxxxxx") == NULL);

    hashT_destroy(ht);
}

void hashT_reinsert_into_deleted_slot_test() {
    HashTable *ht = hashT_create(4, hashString, compareString, free, free);

    hashT_insert(ht, strdup("key1"), strdup("A"));
    hashT_insert(ht, strdup("key2"), strdup("B"));

    hashT_remove(ht, "key1"); 

    hashT_insert(ht, strdup("key3"), strdup("C")); 

    assert(strcmp(hashT_search(ht, "key3"), "C") == 0);
    assert(ht->size == 2);

    hashT_destroy(ht);
}

void hashT_resize_ignores_deleted_test() {
    HashTable *ht = hashT_create(4, hashString, compareString, free, free);

    hashT_insert(ht, strdup("a"), strdup("1"));
    hashT_insert(ht, strdup("b"), strdup("2"));
    hashT_insert(ht, strdup("c"), strdup("3"));

    hashT_remove(ht, "b");

    size_t old_size = ht->size;

    hashT_resize(ht, 16);

    assert(ht->size == old_size); 
    assert(hashT_search(ht, "b") == NULL);
    assert(strcmp(hashT_search(ht, "a"), "1") == 0);
    assert(strcmp(hashT_search(ht, "c"), "3") == 0);

    hashT_destroy(ht);
}

void hashT_mass_delete_chain_test() {
    HashTable *ht = hashT_create(8, badHash, compareString, free, free);

    for (int i = 0; i < 6; i++)
        hashT_insert(ht, strdup((char[4]){ 'a'+i,0 }), strdup("x"));

    hashT_remove(ht, "b");
    hashT_remove(ht, "c");
    hashT_remove(ht, "d");

    assert(hashT_search(ht, "a") != NULL);
    assert(hashT_search(ht, "e") != NULL);
    assert(hashT_search(ht, "f") != NULL);

    hashT_destroy(ht);
}




void runAllTests() {
    hashT_auto_resize_test();
    hashT_all_collisions_test();
    hashT_delete_chain_middle_test();
    hashT_reinsert_after_delete_test();
    hashT_null_value_test();
    hashT_big_stress_test();
    hashT_foreach_after_delete_test();
    hashT_search_not_found_full_table_test();
    hashT_update_value_test();
    hashT_empty_destroy_test();
    hashT_search_wraparound_test();
    hashT_reinsert_into_deleted_slot_test();
    hashT_resize_ignores_deleted_test();
    hashT_mass_delete_chain_test();

    printf("POBEDA\n");
}
