/*
dp + bfs
通常走迷宫的时候，都只有行x和列y两个状态，此题又多了一个状态，就是飞行棋的使用次数k
dp[i][j][k] 表示最多使用K次飞行器，到达到位置(i, j)时，所走的最少步数
操作分为5种，分别为上下左右和从对称点使用飞行器
dP[i][j][k] = min(
      dp[i-1][j][k], // 向下走走到i,j
      dp[i+1][j][k], // 向上走走到i,j
      dp[i][j+1][k], // 向左走走到i,j
      dp[i][j+1][k], // 向右走走到i,j
      dp[row - 1 - i][col - 1 - j][k - 1], // 从对称点使用飞行器
) + 1
目标是dp[endx][endy][5] //题目设定最多使用5次飞行器
初始状态
  dp[startx][start][k] = 0;  k ~ (0,5)
但要注意的是，此题并不是完全按照状态转移方程去计算的，因为要按bfs的顺序遍历
*/
#include <bits/stdc++.h>

using namespace std;

int direction[4][2] = {-1, 0, 1, 0, 0, 1, 0, -1};

struct Point {
    int x;
    int y;
    Point() {};
    Point(int x, int y) : x(x), y(y) {};
};

int main() {
    int row;
    int col;
    cin >> row;
    cin >> col;
    Point start, end;
    vector<vector<char> > mat(row, vector<char>(col, 0));
    int dp[row][col][6];
    for(int i = 0; i < row; ++i)
    for(int j = 0; j < col; ++j) {
        cin >> mat[i][j];
        if(mat[i][j] == 'S') {
            start.x = i;
            start.y = j;
        }
        if(mat[i][j] == 'E') {
            end.x = i;
            end.y = j;
        }
        for(int k = 0; k < 6; ++k) {
            if(i == start.x && j == start.y) dp[i][j][k] = 0;
            else dp[i][j][k] = row * col + 1;
        }
    }
    queue<Point> q;
    q.push(start);
    while(! q.empty()) {
        Point cur = q.front(); q.pop();
        for(int i = 0; i < 4; i++) {
            int targetx = cur.x + direction[i][0];
            int targety = cur.y + direction[i][1];
            if(targetx >= 0 && targetx < row && targety >= 0 && targety < col && mat[targetx][targety] != '#') {
                int flag = 0;
                for(int k = 0; k < 6; k++) {
                    if(dp[targetx][targety][k] > dp[cur.x][cur.y][k] + 1) {
                        dp[targetx][targety][k] = dp[cur.x][cur.y][k] + 1;
                        flag = 1;
                    }
                }
                if(flag) q.push(Point(targetx, targety));
            }
        }
        // 飞行
        int targetx = row - cur.x - 1;
        int targety = col - cur.y - 1;
        if(mat[targetx][targety] != '#') {
            int flag = 0;
            for(int k = 0; k < 5; k++) {
                if(dp[targetx][targety][k + 1] > dp[cur.x][cur.y][k] + 1) {
                    dp[targetx][targety][k + 1] = dp[cur.x][cur.y][k] + 1;
                    flag = 1;
                }
            }
            if(flag) q.push(Point(targetx, targety));
        }
    }
    if(dp[end.x][end.y][5] == row * col + 1) cout << -1 << endl;
    else cout << dp[end.x][end.y][5] << endl;
    return 0;
}