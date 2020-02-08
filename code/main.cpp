#include <iostream>
#include "sort.h"

using namespace std;

void testSort();

int main() {
    testSort();
}

void testSort() {
    int a[17] = {2,6,8,3,1,245,6,7,84,4,2,34,6756,7567,3424,23423,234234};
    heapSort(a, 17);
    for(int i = 0; i < 17; i++) {
        cout << a[i] << " ";
    }
    cout << endl;

}
