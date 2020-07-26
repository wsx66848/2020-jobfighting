#include <bits/stdc++.h>

using namespace std;

 bool isSame(vector<int>& rock) {
     if(rock.size() <= 1) return false;
     for(int i = 0; i < rock.size() -  1; ++i) {
         if(rock[i] == rock[i+1]) {
             continue;
         } else {
             return false;
         }
     }
     return true;
 }

//person 1 man -1 women
 int move(vector<int>& rock, int n, int person) {
     bool flag = true;
     for(int i = 0; i < n; ++i) {
         if(rock[i] > 0) {
             flag = false;
             break;
         }
     }
     if(flag) return person;
     sort(rock.begin(), rock.end());
     for(int i = n - 1; i >= 0; --i) {
         if(rock[i] > 0) {
             rock[i]--;
             if(isSame(rock)) {
                 rock[i]++;
                 continue;
             }
            return move(rock, n, person * -1);
         }
     }
     return person;

 }


int main() {
    int T;
    cin >> T;
    while(T--) {
        int n;
        cin >> n;
        vector<int> rock(n,0);
        for(int i = 0; i < n; i++) cin >> rock[i];
        int person = move(rock, n, 1);
        if(person == 1) {
            cout << "woman" << endl;
        } else if(person == -1){
            cout << "man" << endl;
        }
    }
}