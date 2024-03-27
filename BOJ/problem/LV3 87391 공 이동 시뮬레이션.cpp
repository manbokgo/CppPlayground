// URL: https://school.programmers.co.kr/learn/courses/30/lessons/87391
// Algo: 시뮬레이션

// Start:	240327 17 05
// Read:	0 2
// Think:	0 50
// Code:	0 58
// Total:	1 50

// 정말 힘들게 풀었다..

#include <bits/stdc++.h>
using namespace std;

long long solution(int n, int m, int startY, int startX, vector<vector<int>> queries)
{
    int LTy = startY;
    int LTx = startX;
    int RBy = startY + 1;
    int RBx = startX + 1;

    for (int i = queries.size() - 1; i >= 0; --i)
    {
        int dir = queries[i][0];
        int num = queries[i][1];

        if (dir == 0) // 동
        {
            if (LTx != 0) LTx += num;
            RBx += num;

            if (RBx > m) RBx = m;
        }
        else if (dir == 1) // 서
        {
            LTx -= num;
            if (RBx != m) RBx -= num;

            if (LTx < 0) LTx = 0;
        }
        else if (dir == 2) // 남
        {
            if (LTy != 0) LTy += num;
            RBy += num;

            if (RBy > n) RBy = n;
        }
        else if (dir == 3) // 북
        {
            LTy -= num;
            if (RBy != n) RBy -= num;

            if (LTy < 0) LTy = 0;
        }

        if (LTy >= RBy || LTx >= RBx)
            return 0;
    }

    return ((long long)RBy - LTy) * ((long long)RBx - LTx);
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<vector<int>> tmp = {{2, 1}, {0, 1}, {1, 1}, {0, 1}, {2, 1}};
    vector<vector<int>> tmp2 = {{3, 1}, {2, 2}, {1, 1}, {2, 3}, {0, 1}, {2, 1}};
    cout << solution(2, 2, 0, 0, move(tmp));
    // cout << solution(2, 5, 0, 1, move(tmp2));
}
