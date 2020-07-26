#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int num;
    cin >> num;
    if(num < 5) cout << 1 << endl;
    else if(num < 10) cout << (num - 3) << endl;
    else {
    int start = 6;
    int incre = 2;
    int res = 0;
    for(int i = 10; i <= num; i++) {
         res = start + incre;
         start = res;
         incre += 1;
    }
    cout << res << endl;
    }
    return 0;
}