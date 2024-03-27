// URL: https://school.programmers.co.kr/learn/courses/30/lessons/87391
// Algo: 

// Start:	240327 17 05
// Read:	0 2
// Think:	0 50
// Code:	0 37
// Total:	

#include <bits/stdc++.h>
using namespace std;

int dy[4] = {1, -1, 0, 0};
int dx[4] = {0, 0, 1, -1}; // 북남서동
bool OOB(int y, int x, int n, int m) { return y < 0 || y >= n || x < 0 || x >= m; }
using ll = long long;


ll solution(int m, int n, int curY, int curX, vector<vector<int>> queries) {
    int ansY = 1;
    int ansX = 1;
    
    int trigY = -1;
    int trigX = -1;
    for (int i = queries.size() - 1; i >= 0; --i)
    {
        int dir = queries[i][0];
        int num = queries[i][1];
        
        if (trigY == -1)
        {
            if (curY == 0) trigY = 1;
            else if (curY == n-1) trigY = 0;
        }
        if (trigX == -1)
        {
            if (curX == 0) trigX = 3;
            else if (curX == n-1) trigX = 2;
        }
        
        curY += dy[dir] * num;
        curX += dx[dir] * num;
        if (OOB(curY, curX, n, m))
            return 0;
        
        if (trigY != -1 && dir / 2 == 0)
        {
            if (dir == trigY) ansY += num;
            else ansY -= num;

            ansY = clamp(ansY, 0, n - 1);
        }
        
        if (trigX != -1 && dir / 2 == 1)
        {
            if (dir == trigX) ansX += num;
            else ansX -= num;

            ansX = clamp(ansX, 0, m - 1);
        }
        
        if (ansY == 0 || ansX == 0 )
            return 0;
    }
    
    return ansY * ansX;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<vector<int>> tmp = {{2, 1}, {0, 1}, {1, 1}, {0, 1}, {2, 1}};
    vector<vector<int>> tmp2 = {{3, 1}, {2, 2}, {1, 1}, {2, 3}, {0, 1}, {2, 1}};
    // cout << solution(2, 2, 0, 0, move(tmp));
    cout << solution(2, 5, 0, 1, move(tmp2));
}
