#include <bits/stdc++.h>

using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> num(n);
    for(int i = 0; i < n; i++) {
        cin >> num[i];
    }
    stack<int> s;
    vector<int> res;
    for(int i = 0; i < n; i++) {
        while(! s.empty() && num[s.top()] <= num[i]) {
            s.pop();
        }
        if(! s.empty()) res.push_back(i - s.top());
        else  res.push_back(0);
        s.push(i);
    }
    for(int i = 0; i < n; i++) {
        cout << res[i] << " ";
    }
    cout << endl;
    return 0;
}