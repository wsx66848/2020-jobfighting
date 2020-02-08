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

void quickSort(int* a , int l , int r) {
    if(l < r) {
        int pivot = partition(a, l, r);
        quickSort(a, pivot+1, r);
        quickSort(a, l, pivot - 1);  
    }
}
int partition(int* a, int l , int r) {
    int pivot = a[l]; // 以左边第一个数作为基准，将所有大于它的值移到右侧，所有小于它的值移到左侧
    while(l < r) {
        while(l < r && a[r] >= pivot) {
            r--;
        }
        swap(a[l], a[r]);
        while(l < r && a[l] <= pivot) {
            l++;
        }
        swap(a[l], a[r]);
    }
    return l;
}

void mergeSort(int* a, int l, int r, int* temp) {
     if(l < r) {
         int median = (l + r) / 2;
         mergeSort(a, l, median, temp);
         mergeSort(a, median+1, r, temp);
         merge(a, l, median, r, temp);
     }
 }

 void merge(int* a, int l, int median, int r, int* temp) {
     int left = l;
     int right = median + 1;
     int t = 0;
     while(left <= median && right <= r) {
         if(a[left] < a[right]) {
             temp[t++] = a[left++];
         } else {
             temp[t++] = a[right++];
         }
     }
     while(left <= median) {
         temp[t++] = a[left++];
     }
     while(right <= r) {
         temp[t++] = a[right++];
     }
     t = 0;
     while(l <= r) {
         a[l++] = temp[t++];
     }
 }

 void bubbleSort(int* a, int size) {
    for (int i = 0; i < size; i++) {
            bool flag = true;//设定一个标记，若为true，则表示此次循环没有进行交换，也就是待排序列已经有序，排序已然完成。
            for (int j = 0; j < size - 1 - i; j++) {
                if (a[j] > a[j + 1]) {
                    swap(a[j], a[j+1]);
                    flag = false;
                }
            }
            if (flag) {
                break;
            }
        }
}

void selectSort(int* a, int size) {
    for (int i = 0; i < size; i++) {
            int min = i;//每一趟循环比较时，min用于存放较小元素的数组下标，这样当前批次比较完毕最终存放的就是此趟内最小的元素的下标，避免每次遇到较小元素都要进行交换。
            for (int j = i + 1; j < size; j++) {
                if (a[j] < a[min]) {
                    min = j;
                }
            }
            //进行交换，如果min发生变化，则进行交换
            if (min != i) {
                swap(a[min],a[i]);
            }
        }
}