#include <bits/stdc++.h>

using namespace std;
/*
有一叠扑克牌，每张牌介于1和10之间

有四种出牌方法：

单出1张
出2张对子
出五张顺子，如12345
出三连对子，如112233
给10个数，表示1-10每种牌有几张，问最少要多少次能出完

带备忘录的深搜
状态就是一个10元组(记录每张牌的剩余张数)，
操作就是5种 单出1张 出2张对子 出5张顺子 出三连对子
*/
#include <bits/stdc++.h>

using namespace std;

int card[10];
int mem[5][5][5][5][5][5][5][5][5][5];
int Max;

int play() {
    int& res = mem[card[0]][card[1]][card[2]][card[3]][card[4]][card[5]][card[6]][card[7]][card[8]][card[9]];
    if(res != 0) return res;

    bool flag = true;
    for(int i = 0; i < 10; i++) {
        if(card[i]) {
            flag = false;
            break;
        }
    }
    //达到无牌状态
    if(flag) return 0;

    res = Max;

    //出顺子
    for(int i = 0; i < 6; i++) {
        if(card[i] && card[i+1] && card[i+2] && card[i+3] && card[i+4]) {
            for(int j = 0; j < 5; j++) card[i+j]--;
            int tmp = play() + 1;
            if(res > tmp) res = tmp;
            for(int j = 0; j < 5; j++) card[i+j]++;
        }
    }

    //出连对
    for(int i = 0; i < 8; i++) {
        if(card[i] >= 2 && card[i+1] >= 2 && card[i+2] >= 2) {
            for(int j = 0; j < 3; j++) card[i+j] -= 2;
            int tmp = play() + 1;
            if(res > tmp) res = tmp;
            for(int j = 0; j < 3; j++) card[i+j] += 2;
        }
    }

    //出对
    for(int i = 0; i < 10; i++) {
        if(card[i] >= 2) {
            card[i] -= 2;
            int tmp = play() + 1;
            if(res > tmp) res = tmp;
            card[i] += 2;
        }
    }


    //出单
    for(int i = 0; i < 10; i++) {
        if(card[i] >= 1) {
            card[i] -= 1;
            int tmp = play() + 1;
            if(res > tmp) res = tmp;
            card[i] += 1;
        }
    }

    return res;
}

int main() {
    for(int i = 0; i < 10; i++) {
        cin >> card[i];
        Max += card[i];
    }
    Max += 1;
    cout << play() << endl;
    return 0;
}