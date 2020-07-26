/*
DNA 碱基对  最少次数 ATTTAA -> TTAATT 只能移动或修改
类似贪心，因为字符串的长度一样，如果移动时能找到一个位置和它不同并且那个位置处本身已不同的话，交换两个字符串的位置，这样只需操作一次
先移，能移就移
*/
#include <bits/stdc++.h>

using namespace std;

int main() {
    string s1;
    string s2;
    cin >> s1 >> s2;
    int count = 0;
    for(int i = 0; i < s1.size(); i++) {
        if(s1[i] ==  s2[i]) continue;
        for(int j = i+1; j < s1.size(); j++) {
            if(s1[j] != s1[i] && s1[j] != s2[j]) {
                char temp = s1[j];
                s1[j] = s1[i];
                s1[i] = temp;
                break;
            }
        }
        count++;
    }
    cout << count << endl;
}