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
        while(! s.empty() && s.top() <= num[i]) {
            s.pop();
        }
        if(s.size() == 1) res.push_back(i);
        s.push(num[i]);
    }
    for(int i = 0; i < res.size(); i++) {
        cout << res[i] << " ";
    }
    cout << endl;
    return 0;
}