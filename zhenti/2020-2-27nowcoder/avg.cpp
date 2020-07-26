#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int num;
    scanf("%d", &num);
    int size = num * 3;
    vector<int> number;
    for(int i = 0; i < size; i++) {
        int temp;
        scanf("%d", &temp);
        number.push_back(temp);
    }
    sort(number.begin(), number.end());
    long int result = 0;
    for(int i = size - 2, res = 0; i >= 0 && res < num; i -= 2) {
        result += number[i];
        res++;
    }
    cout << result << endl;

}