/*
牛家庄幼儿园为庆祝61儿童节举办庆祝活动,庆祝活动中有一个节目是小朋友们围成一个圆圈跳舞。牛老师挑选出n个小朋友参与跳舞节目,已知每个小朋友的身高h_i。为了让舞蹈看起来和谐,牛老师需要让跳舞的圆圈队形中相邻小朋友的身高差的最大值最小,牛老师犯了难,希望你能帮帮他。

如样例所示:
当圆圈队伍按照100,98,103,105顺时针排列的时候最大身高差为5,其他排列不会得到更优的解。 
输入描述:
输入包括两行,第一行为一个正整数n(3 ≤ n ≤ 20)
第二行为n个整数h_i(80 ≤ h_i ≤ 140),表示每个小朋友的身高。
输出描述:
输出一个整数,表示满足条件下的相邻小朋友身高差的最大值。
//回溯 加比较
*/
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int num;
    cin >> num;
    vector<int> res(num,0);
    for(int i = 0; i < num; i++) {
        cin >> res[i];
    }
    sort(res.begin(), res.end());
    int Min = res[num - 1] - res[0];
    for(int i = 1; i < num - 2; i++) {
        int del_1 = res[num - 1] - res[i];
        int del_2 = res[i + 1] - res[0];
        int Max = max(del_1, del_2);
        if(Max < Min) {
            Min = Max;
        }
    }
    cout << Min << endl;

}