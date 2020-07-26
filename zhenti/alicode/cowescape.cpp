#include<iostream>
#include <vector>

using namespace std;

void walk(vector<int> num, int k, int target, int& count) {
    int size = num.size();
    for(int i = 0; i < size; i++) {
        if(k == 1) {
            if((target - num[i]) % 7 == 0) {
                count++;
            }
            continue;
        }
        vector<int> tmp = num;
        tmp.erase(tmp.begin() + i);
        walk(tmp, k - 1, target - num[i], count);
    }
}

int main() {
    int n;
    int k;
    cin >> n;
    cin >> k;
    int num = 0;
    vector<int> res;
    for(int i = 0; i < n; i++) {
        res.push_back(i);
    }
    walk(res, k, n, num);
    cout << num << endl;
    return 0;
}