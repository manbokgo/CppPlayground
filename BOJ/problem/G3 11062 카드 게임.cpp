// URL: https://www.acmicpc.net/problem/11062
// Algo: DP (MiniMax 트리), 게임 이론

// Start:	240821 13 07
// Read:	0 1
// Think:	0 3
// Code:	0 7
// Total:   0 11

// 그리디하게 근우가 최대값만 뽑으면 안 된다. 당장 더 작은 값이라도 최종적으로 더 큰 합이 될 수 있음.
// 예시) 4 999 3 999 1 2
// 근우: 2 999 999 = 2000
// 명우: 4 3 1 = 8

// 그러니 모든 경우를 검사해야 함 -> O(2^n) 연산 크네 -> DP

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) x.begin(), x.end()
#define pb push_back

int arr[1'000];
int dp[1'000][1'000];

int Solve(int st, int en, bool guen)
{
    if (dp[st][en] != -1) return dp[st][en];
    if (st == en)
    {
        if (guen) return arr[st];
        else return 0;
    }

    if (guen) dp[st][en] = max(arr[st] + Solve(st + 1, en, false), arr[en] + Solve(st, en - 1, false));
    else dp[st][en] = min(Solve(st + 1, en, true), Solve(st, en - 1, true));

    return dp[st][en];
}

int main()
{
    fastio;
    int T;
    cin >> T;

    while (T--)
    {
        memset(dp, -1, sizeof(dp));

        int n;
        cin >> n;
        for (int i = 0; i < n; ++i)
            cin >> arr[i];

        cout << Solve(0, n - 1, true) << '\n';
    }
}
