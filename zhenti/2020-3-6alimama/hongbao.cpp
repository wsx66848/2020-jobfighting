#include <iostream>
#include <stdlib.h>
#include <vector>
#include <time.h>

using namespace std;

bool hongbao(int sum, int people, vector<int>& divid) {
    if(sum < people) return false;
    srand(unsigned(time(NULL)));
    for(int i = 1; i <= people; i++) {
        if(i == people) {
            divid[i - 1] = sum;
            continue;
        }
        int need = sum - (people - i);
        int cur = rand() % need + 1;
        divid[i - 1] = cur;
        sum -= cur;
    }
    return true;
}

int main() {
    int sum = 10, people = 5;
    vector<int> div(5, 0);
    hongbao(sum, people, div);
    for(int i = 0;  i < 5; i++) {
        cout <<  div[i] << " ";
    }
    cout << endl;
    return 0;
}