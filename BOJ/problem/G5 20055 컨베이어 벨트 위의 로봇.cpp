// URL: https://www.acmicpc.net/problem/20055
// Algo: 시뮬레이션

// Start:	240908 22 33
// Read:	0 7
// Think:	0 3
// Code:	0 16
// Total:	0 26

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) x.begin(), x.end()
#define pb push_back

int arr[201];
bool robots[201];

int main()
{
    fastio;
    int n, k;
    cin >> n >> k;

    for (int i = 1; i <= 2 * n; ++i)
        cin >> arr[i];

    int st = 1;
    int en = n;

    int turn = 0;
    int cnt = 0;
    while (cnt < k)
    {
        ++turn;

        // 회전
        --st;
        --en;
        if (st < 1) st = 2 * n;
        if (en < 1) en = 2 * n;

        // 로봇 이동
        robots[en] = false;

        int idx = en;
        for (int loop = 0; loop < n - 1; ++loop)
        {
            --idx;
            if (idx < 1) idx = 2 * n;

            if (!robots[idx]) continue;

            int nxt = idx + 1;
            if (nxt > 2 * n) nxt = 1;

            if (robots[nxt] || arr[nxt] <= 0) continue;
            robots[idx] = false;
            --arr[nxt];
            if (arr[nxt] == 0) ++cnt;
            if (nxt != en) robots[nxt] = true;
        }

        // 로봇 놓기
        if (!robots[st] && arr[st] > 0)
        {
            robots[st] = true;
            --arr[st];
            if (arr[st] == 0) ++cnt;
        }
    }
    cout << turn;
}
