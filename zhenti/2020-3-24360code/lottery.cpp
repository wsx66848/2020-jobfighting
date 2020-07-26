/*
题目 A和B两个人抽奖，奖盒里有n张奖票和m张非奖票，A和B轮流从奖盒抽奖，抽到中奖的人胜利，抽过的将丢弃。若B每次抽奖后没抽到，B会再抽一张并直接丢弃
A先抽，问A的胜率。若最后两人都没有抽到奖则B胜利

递归思路:
模拟抽奖流程，因为要保证A胜利，所以每步都要保证A胜利
f(n,m) 表示从n张奖票和m张非奖票中A先抽胜利的概率
递归终止条件 m == 0 则A必定胜利 返回1 
m == 1时，A此时不抽中就输了 返回 1 - 1 / n + 1
n == 0 A必定失败 返回0
*/
#include <bits/stdc++.h>

using namespace std;

double lottery(int n, int m) {
    if(n == 0) return 0;
    if(m <= 0) return 1;
    if(m == 1) return n * 1.0 / (n + 1);
    //A抽中
    double win = n * 1.0 / (m + n);
    //A没抽中，换B抽，B不能抽中，同时进入B的丢弃环节，又可分为B丢了一张奖票，以及B丢了一张非奖票
    double Bnowin = m * 1.0 / (m + n) * ((m - 1) * 1.0 / (m + n - 1));
    //B丢了一张奖票
    double lostlottery = n * 1.0 / (n + m - 2) * lottery(n - 1, m - 2);
    //B丢了一张非奖票
    double notlost = (m - 2) * 1.0 / (n + m - 2) * lottery(n, m - 3);
    return win + Bnowin * (lostlottery + notlost);
}

int main() {
    int num1;
    int num2;
    double p = 0;
    cin >> num1 >> num2;
    printf("%.4f\n", lottery(num1, num2));
    return 0;
}