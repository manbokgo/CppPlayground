// URL: https://www.acmicpc.net/problem/12865
// Algo: DP

// Start:	240518 21 25
// Read:	0 2
// Think:	0 3
// Code:	0 6
// Total:	0 11

// G5 2293 동전1이 배낭 문제였구나. 이걸 이제야 아네.
// 마찬가지로 i-1만 참조하는 걸 반복하므로 1차원 배열로 바꿔서 풀 수 있다.

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);

// DP 바텀업 1차원배열 8ms 2MB
int dp[100'001];
int main()
{
    fastio;

    int n, k;
    cin >> n >> k;

    for (int i = 1; i <= n; ++i)
    {
        int w, v;
        cin >> w >> v;
        for (int j = k; j >= w; --j) // 실수: 역순으로 순회해야만 dp[j-w]가 i-1 상태의 값을 가리킨다
            dp[j] = max(dp[j], v + dp[j - w]);
    }

    cout << dp[k];
}

// DP 바텀업 32ms 41MB
/*
int dp[101][100'001];
int main()
{
    fastio;

    int n, k;
    cin >> n >> k;

    for (int i = 1; i <= n; ++i)
    {
        int w, v;
        cin >> w >> v;
        for (int j = 1; j <= k; ++j)
        {
            if (w > j) dp[i][j] = dp[i - 1][j];
            else dp[i][j] = max(dp[i - 1][j], v + dp[i - 1][j - w]);
        }
    }

    cout << dp[n][k];
}
*/


// DP 탑다운 56ms 41MB
/*
using pii = pair<int, int>;
pii goods[101];
int dp[101][100'001];

int solve(int i, int w)
{
    if (dp[i][w] != -1) return dp[i][w];

    const auto [cW, cV] = goods[i];
    if (cW > w) return dp[i][w] = solve(i - 1, w);
    else return dp[i][w] = max(solve(i - 1, w), cV + solve(i - 1, w - cW));
}

int main()
{
    fastio;

    int n, k;
    cin >> n >> k;

    memset(dp, -1, sizeof(dp));
    for (int i = 0; i < 100'001; ++i)
        dp[0][i] = 0;

    for (int i = 0; i < 101; ++i)
        dp[i][0] = 0;

    for (int i = 1; i <= n; ++i)
    {
        auto& [w, v] = goods[i];
        cin >> w >> v;
    }

    cout << solve(n, k);
}
*/
