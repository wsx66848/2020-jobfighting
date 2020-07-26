#include <bits/stdc++.h>

using namespace std;

int ppow(int x) {
    long long res = 1;
    long long base = 2;
    while(x) {
        if(x % 2 == 0) {
            base *= base;
            base = base % 1000000007;
            x /= 2;
        } else {
            res = res * base;
            res = res % 1000000007;
            x = x - 1;
        }
    }
    return res;
}

int main() {
    int num;
    cin >> num;
    int res =  num * ppow(num - 1);
    res = res % 1000000007;
    cout << res << endl;
    return 0;
}