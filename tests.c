#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "compare.h"
#include "swap.h"
#include "bubbleSort.h"

void swapTest1(){
    int a = 1, b = 2;
    swap(&a, &b, sizeof(int));
    assert(a == 2 && b == 1);
}

void swapTest2(){
    char a = 'a', b = 'b';
    swap(&a, &b, sizeof(char));
    assert(a == 'b' && b == 'a');
}

void swapTest3(){
    double a = 1.0, b = 2.0;
    swap(&a, &b, sizeof(double));
    assert(a == 2.0 && b == 1.0);
}

void swapTest4(){
    char *a = "abc", *b = "def";
    swap(&a, &b, sizeof(char *));
    assert(strcmp(a, "def") == 0 && strcmp(b, "abc") == 0);
}

void compareTest1(){
    int a = 1, b = 2;
    assert(compareInt(&a, &b) < 0);
}

void compareTest2(){
    char a = 'a', b = 'b';
    assert(compareChar(&a, &b) < 0);
}

void compareTest3(){
    double a = 1.0, b = 2.0;
    assert(compareDouble(&a, &b) < 0);
}

void compareTest4(){
    char *a = "abc", *b = "def";
    assert(compareString(&a, &b) < 0);
}

void bubbleSortTest1(){
    int a[] = {1, 2, 3, 4, 5};
    bubbleSort(a, sizeof(a) / sizeof(int), sizeof(int), compareInt);
    assert(a[0] == 1 && a[1] == 2 && a[2] == 3 && a[3] == 4 && a[4] == 5);
}

void bubbleSortTest2(){
    char a[] = {'a', 'b', 'c', 'd', 'e'};
    bubbleSort(a, sizeof(a) / sizeof(char), sizeof(char), compareChar);
    assert(a[0] == 'a' && a[1] == 'b' && a[2] == 'c' && a[3] == 'd' && a[4] == 'e');
}

void bubbleSortTest3(){
    double a[] = {1.0, 2.0, 3.0, 5.0, 4.0};
    bubbleSort(a, sizeof(a) / sizeof(double), sizeof(double), compareDouble);
    assert(a[0] == 1.0 && a[1] == 2.0 && a[2] == 3.0 && a[3] == 4.0 && a[4] == 5.0);
}

void bubbleSortTest5(){
    double a[] = {1.0, 2.0, 5.0, 3.0, 1.0};
    bubbleSort(a, sizeof(a) / sizeof(double), sizeof(double), compareDouble);
    assert(a[0] == 1.0 && a[1] == 1.0 && a[2] == 2.0 && a[3] == 3.0 && a[4] == 5.0);
}

void bubbleSortTest4(){
    char *a[] = {"abc", "def", "ghi", "jkl", "mno"};
    bubbleSort(a, sizeof(a) / sizeof(char *), sizeof(char *), compareString);
    assert(strcmp(a[0], "abc") == 0 && strcmp(a[1], "def") == 0 && strcmp(a[2], "ghi") == 0 && strcmp(a[3], "jkl") == 0 && strcmp(a[4], "mno") == 0);
}

void bubbleSortEmptyTest() {
    int arr[1];
    bubbleSort(arr, 0, sizeof(int), compareInt);
}

void bubbleSortSingleElementTest() {
    int a[] = {42};
    bubbleSort(a, 1, sizeof(int), compareInt);
    assert(a[0] == 42);
}

void bubbleSortNearlySortedTest() {
    int a[] = {1, 2, 4, 3, 5};
    bubbleSort(a, 5, sizeof(int), compareInt);
    assert(a[0] == 1 && a[1] == 2 && a[2] == 3 && a[3] == 4 && a[4] == 5);
}

void bubbleSortReversedTest() {
    int a[] = {5, 4, 3, 2, 1};
    bubbleSort(a, 5, sizeof(int), compareInt);
    assert(a[0] == 1 && a[1] == 2 && a[2] == 3 && a[3] == 4 && a[4] == 5);
}

void bubbleSortRandomTest() {
    int a[] = {7, 2, 9, 1, 5, 6, 3, 8, 4};
    bubbleSort(a, 9, sizeof(int), compareInt);
    for (int i = 0; i < 8; i++) {
        assert(a[i] <= a[i+1]);
    }
}

void bubbleSortAllEqualTest() {
    int a[15];
    for (int i = 0; i < 15; i++) a[i] = 2;
    bubbleSort(a, 15, sizeof(int), compareInt);
    for (int i = 0; i < 15; i++) {
        assert(a[i] == 2);
    }
}

void bubbleSortStressTest() {
    const int N = 1000;
    int *a = malloc(N * sizeof(int));
    for (int i = 0; i < N; i++) {
        a[i] = rand() % 1000;
    }
    bubbleSort(a, N, sizeof(int), compareInt);
    for (int i = 0; i < N - 1; i++) {
        assert(a[i] <= a[i+1]);
    }
    free(a);
}

void runAllTests(){
    swapTest1();
    swapTest2();
    swapTest3();
    swapTest4();
    compareTest1();
    compareTest2();
    compareTest3();
    compareTest4();
    bubbleSortTest1();
    bubbleSortTest2();
    bubbleSortTest3();
    bubbleSortTest4();
    bubbleSortTest5();
    bubbleSortEmptyTest();
    bubbleSortSingleElementTest();
    bubbleSortNearlySortedTest();
    bubbleSortReversedTest();
    bubbleSortRandomTest();
    bubbleSortAllEqualTest();
    bubbleSortStressTest();

    printf("Pobeda\n");
}


//тесты с массивом из одного и того же 15 двоек
/*
Пустой массив
Массив из 1 элемента
Почти отсортированный
Перевернутый
Рандомный массив
Нагрузочный массив
*/