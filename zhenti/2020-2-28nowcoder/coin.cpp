#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;


float  fetch(int n,  float coin,  float gold) {
    if(n == 1) return gold / coin;
    return gold / coin +  (coin - gold) / coin * fetch(n-1, coin - 1, gold);
} 

int main() {
    int num;
    scanf("%d", &num);
    if(num == 0) printf("%.6f", 0);
    else if(num <= 1000 && num > 990) printf("%.6f", 1);
    else {
        printf("%.12f", fetch(num, 1000 * 1.0, 10 * 1.0));
    }
    
}