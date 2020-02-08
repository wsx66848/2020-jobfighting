#ifndef MY_SORT_H
#define MY_SORT_H
void heapSort(int* a, int size);
void createHeap(int* a, int size, int lastIndex);
void swap(int& a, int& b);
void quickSort(int* a , int l , int r);
int partition(int* a, int l , int r);
void mergeSort(int* a, int l, int r, int* temp);
void merge(int* a, int l, int median, int r, int* temp);
void bubbleSort(int* a, int size);
void selectSort(int* a, int size);
#endif