#include <iostream>
#include <cstdio>
#include <vector>
#include <stack>

using namespace std;

int main() {
    int num;
    scanf("%d", &num);
    vector<int> number;
    for(int i = 0; i < num; i++) {
        int temp;
        scanf("%d", &temp);
        number.push_back(temp);
    }
    stack<int> s1;
    stack<int> s2;
    int op;
    int res = 0;
    for(int i = 0; i < num; i++) {
        if(s1.size() == 0) {
            s1.push(number[i]);
        } else {
            int n = s1.top();
            if(n == number[i]) {
                s1.push(number[i]);
                continue;
            }
            if(s1.size() == 1) {
                if(n > number[i]) op = 1; //减
                else op = 2; //增
                s1.push(number[i]);
            } else {
                if(n > number[i]) {
                    if(op == 1) s1.push(number[i]);
                    else if(op == 0) {
                        s1.push(number[i]);
                        op = 1; 

                    } else {
                        res++;
                        s1 = s2;
                        op = 0;
                        s1.push(number[i]);
                    }
                } else {
                    if(op == 2) s1.push(number[i]);
                    else if(op == 0) {
                        s1.push(number[i]);
                        op = 2; 
                    }
                    else {
                        res++;
                        s1 = s2;
                        op = 0;
                        s1.push(number[i]);
                    }
                }
            }

        }
    }
    if(!s1.empty()) res++;
    cout << res << endl;
}
