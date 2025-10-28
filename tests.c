#include <stdio.h>
#include <assert.h>
#include "compare.h"
#include <string.h>
#include "mergeSort.h"

void mergeSortTest1(){
    int a[] = {100, -200, 0, 300, -1};
    mergeSort(a, 0, 4, sizeof(int), compareInt);
    assert(a[0] == -200 && a[1] == -1 && a[2] == 0 && a[3] == 100 && a[4] == 300);
}
//
void mergeSortTest2(){
    char a[] = {'z', 'A', 'm', 'B', '0'};
    mergeSort(a, 0, 4, sizeof(char), compareChar);
    assert(a[0] == '0' && a[1] == 'A' && a[2] == 'B' && a[3] == 'm' && a[4] == 'z');
}
//
void mergeSortTest3(){
    double a[] = {3.14, -2.71, 0.0, -0.0, 1e10, -1e5};
    mergeSort(a, 0, 5, sizeof(double), compareDouble);
    assert(a[0] == -1e5 && a[1] == -2.71 && a[2] == -0.0 && a[3] == 0.0 && a[4] == 3.14 && a[5] == 1e10);
}
//
void mergeSortTest4(){
    char *a[] = {"banana", "Apple", "cherry", "Date", "elderberry"};
    mergeSort(a, 0, 4, sizeof(char *), compareString);
    assert(a[0] == "Apple" && a[1] == "Date" && a[2] == "banana" && a[3] == "cherry" && a[4] == "elderberry");
}
//
void mergeSortEmptyTest() {
    int arr[1];
    mergeSort(arr, 0, 0, sizeof(int), compareInt);
}
//
void mergeSortSingleElementTest() {
    double a[] = {42.5};
    mergeSort(a, 0, 0, sizeof(double), compareDouble);
    assert(a[0] == 42.5);
}
//
void mergeSortAllEqualTest() {
    char a[20];
    for (int i = 0; i < 20; i++) a[i] = 'x';
    mergeSort(a, 0, 19, sizeof(char), compareChar);
    for (int i = 0; i < 20; i++) assert(a[i] == 'x');
}
//
void mergeSortDuplicatesTest() {
    int a[] = {5, 2, 8, 2, 9, 1, 5, 5};
    mergeSort(a, 0, 7, sizeof(int), compareInt);
    int expected[] = {1, 2, 2, 5, 5, 5, 8, 9};
    for (int i = 0; i < 8; i++) assert(a[i] == expected[i]);
}
//
void mergeSortReversedTest() {
    int a[] = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
    mergeSort(a, 0, 9, sizeof(int), compareInt);
    for (int i = 0; i < 10; i++) assert(a[i] == i);
}
//
void mergeSortRandomTest() {
    int a[] = {17, -3, 0, 42, -17, 99, 1, 0, 2, -42};
    mergeSort(a, 0, 9, sizeof(int), compareInt);
    for (int i = 0; i < 9; i++) assert(a[i] <= a[i+1]);
}
//
void runAlltests(){
    mergeSortTest1();
    mergeSortTest2();
    mergeSortTest3();
    mergeSortTest4();
    mergeSortEmptyTest();
    mergeSortSingleElementTest();
    mergeSortAllEqualTest();
    mergeSortDuplicatesTest();
    mergeSortReversedTest();
    mergeSortRandomTest();
    printf("PABEDA");
}//