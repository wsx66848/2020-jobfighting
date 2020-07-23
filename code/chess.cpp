#include <bits/stdc++.h>

using namespace std;

int numRookCaptures(vector<vector<char>>& board) {
        int posX, posY;
        for(int i = 0; i < 8; i++) {
            int flag = 0;
            for(int j = 0; j < 8; j++) {
                if(board[i][j] == 'R') {
                    posX = i;
                    posY = j;
                    flag = 1;
                    break;
                }
            }
            if(flag) break;
        }
        queue<pair<int, vector<int>>> q;
        q.push(make_pair(0, vector<int>{posX, posY}));
        int count = 0;
        while(! q.empty()) {
            auto walk = q.front();
            q.pop();
            auto pos = walk.second;
            if(board[pos[0]][pos[1]] == 'B') continue;
            if(board[pos[0]][pos[1]] == 'p') count++;
            if(pos[1] < 7 && (walk.first == 0 || walk.first == 1)) {
                q.push(make_pair(1, vector<int>{pos[0], pos[1] + 1}));
            }
            if(pos[1] > 0 && (walk.first == 0 || walk.first == -1)) {
                q.push(make_pair(-1, vector<int>{pos[0], pos[1] - 1}));
            }
            if(pos[0] < 7 && (walk.first == 0 || walk.first == 2)) {
                q.push(make_pair(2, vector<int>{pos[0] + 1, pos[1]}));
            }
            if(pos[0] > 0 && (walk.first == 0 || walk.first == -2)) {
                q.push(make_pair(-2, vector<int>{pos[0] - 1, pos[1]}));
            }
        }
        return count;
    }

int main() {
    char a[8][8] = {{'.','.','.','.','.','.','.','.'},
    {'.','.','.','p','.','.','.','.'},
    {'.','.','.','R','.','.','.','p'},
    {'.','.','.','.','.','.','.','.'},
    {'.','.','.','.','.','.','.','.'},
    {'.','.','.','p','.','.','.','.'},
    {'.','.','.','.','.','.','.','.'},
    {'.','.','.','.','.','.','.','.'}};
    vector<vector<char> > chess(8, vector<char>(8));
    for(int i = 0; i < 8; i++)
    for(int j = 0; j < 8; j++) {
        chess[i][j] = a[i][j];
    }
    int count = numRookCaptures(chess);
    cout << count << endl;
}