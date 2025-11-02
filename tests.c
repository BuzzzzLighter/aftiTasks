#include "deque.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>


void test_resize_from_zero() {
    Deque dq;
    deque_init(&dq, 0, sizeof(int));
    int x = 42;
    deque_push_back(&dq, &x);
}

void test_wrap_around_after_resize() {
    Deque dq;
    deque_init(&dq, 2, sizeof(int));

    int vals[] = {10, 20, 30, 40, 50};
    for (int i = 0; i < 5; i++) deque_push_back(&dq, &vals[i]);

    int out;
    deque_pop_front(&dq, &out); assert(out == 10);
    deque_pop_back(&dq, &out);  assert(out == 50);
    deque_pop_front(&dq, &out); assert(out == 20);
    deque_pop_back(&dq, &out);  assert(out == 40);
    deque_pop_front(&dq, &out); assert(out == 30);

    assert(deque_empty(&dq));
}

void test_mixed_push_resize() {
    Deque dq;
    deque_init(&dq, 3, sizeof(int));

    int a = 1, b = 2, c = 3, d = 4;
    deque_push_front(&dq, &a);
    deque_push_back(&dq, &b);
    deque_push_front(&dq, &c);
    deque_push_back(&dq, &d);

    int out;
    deque_pop_front(&dq, &out); assert(out == 3);
    deque_pop_front(&dq, &out); assert(out == 1);
    deque_pop_back(&dq, &out);  assert(out == 4);
    deque_pop_back(&dq, &out);  assert(out == 2);
}

void test_get_with_wrapping() {
    Deque dq;
    deque_init(&dq, 4, sizeof(int));

    int vals[] = {100, 200, 300};
    for (int i = 0; i < 3; i++) deque_push_back(&dq, &vals[i]);

    int temp = 0;
    deque_pop_front(&dq, &temp);

    int out;
    deque_get(&dq, 0, &out); assert(out == 200);
    deque_get(&dq, 1, &out); assert(out == 300);
}

typedef struct { 
    char name[10]; 
    int id; 
} Person;

void test_struct_elements() {
    Deque dq;
    deque_init(&dq, 2, sizeof(Person));

    Person p1 = {"Alice", 1};
    Person p2 = {"Bob", 2};
    deque_push_back(&dq, &p1);
    deque_push_front(&dq, &p2);

    Person out;
    deque_get(&dq, 0, &out);
    assert(strcmp(out.name, "Bob") == 0 && out.id == 2);

    deque_get(&dq, 1, &out);
    assert(strcmp(out.name, "Alice") == 0 && out.id == 1);
}
void test_pop_empty() {
    Deque dq;
    deque_init(&dq, 4, sizeof(int));

    int out = 999;
    deque_pop_front(&dq, &out);
    assert(out == 999);
    assert(deque_size(&dq) == 0);
    assert(deque_empty(&dq));
}

void test_pop_single_element_twice() {
    Deque dq;
    deque_init(&dq, 4, sizeof(int));

    int x = 42;
    deque_push_back(&dq, &x);

    int out;
    deque_pop_back(&dq, &out);
    assert(out == 42);
    assert(deque_empty(&dq));

    int y = 999;
    deque_pop_back(&dq, &y);
    assert(y == 999);
}

void runAllTests() {
    test_resize_from_zero();
    test_wrap_around_after_resize();
    test_mixed_push_resize();
    test_get_with_wrapping();
    test_struct_elements();
    test_pop_empty();
    test_pop_single_element_twice();
    printf("Tests passed\n");
}