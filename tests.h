#ifndef TESTS_H
#define TESTS_H
#include "deque.h"

void runAllTests();
void test_wrap_around_after_resize();
void test_mixed_push_resize();
void test_get_with_wrapping();
void test_struct_elements();
void test_pop_empty();
void test_pop_single_element_twice();
void test_peek_on_empty();
void test_peek_simple();
void test_peek_after_pop();
void test_peek_wraparound();

#endif