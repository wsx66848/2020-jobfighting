#include "sort.h"

void heapSort(int* a, int size) {
    for(int i = 0; i < size; i++) {
        createHeap(a, size, size - 1- i);
        swap(a[0], a[size - 1 -i]);
    }
}

void createHeap(int* a, int size, int lastIndex) {
    for(int i = size / 2 - 1;i >= 0;i--) {
        int t = i;
        while(t * 2 + 1 <= lastIndex) {
            int bigIndex = t * 2 + 1;
            if(bigIndex < lastIndex && a[bigIndex] < a[bigIndex+1]) {  //a[bigIndex] > a[bigIndex + 1]
                bigIndex++;
            }
            if(a[t] < a[bigIndex]) { // a[t] > a[bigIndex] 从小到大
                swap(a[t], a[bigIndex]);
                t = bigIndex;
            } else {
                break;
            }
        }
    }
}

void swap(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}