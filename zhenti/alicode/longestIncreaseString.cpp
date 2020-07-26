#include <bits/stdc++.h>

using namespace std;

static bool compare(const string& a, const string& b) {
    if(a.size() == 0) return true;
    if(b.size() == 0) return false;
    if(a[a.size() - 1] == b[b.size() - 1]) return a[0] < b[0];
    return a[a.size() - 1] < b[b.size() - 1];
}

int main() {
    int num;
    cin >> num;
    vector<string> strs(num);
    for(int i = 0; i < num; i++) {
        cin >> strs[i];
    }
    sort(strs.begin(), strs.end(), compare);
    vector<int> dp(26, 0);
    int Max = -1;
    for(int i = 0; i < strs.size(); i++) {
        if(strs[i].size() == 0) continue;
        string str = strs[i];
        int end = str[str.size() - 1] - 'a';
        int start = str[0] - 'a';
        int temp = 0;
        for(int k = 0; k <= start; k++) {
            temp = max(temp, (int)(dp[k] + str.size()));
        }
        dp[end] = temp;
        Max = max(dp[end], Max);
    }
    cout << Max << endl;
    return 0;
}