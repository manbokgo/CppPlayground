// URL: https://www.acmicpc.net/problem/17404
// Algo: DP

// Start:	240916 08 33
// Read:	0 1
// Think:	0 11
// Code:	0 6
// Total:	0 18

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) x.begin(), x.end()
#define pb push_back

constexpr int INF = 0x3f3f3f3f;

int n;
int cost[1'001][3];
int dp[1'001][3]; // i번째 집을 c로 칠했을 때, 그 때까지의 최소 비용

int main()
{
    fastio;
    cin >> n;
    for (int i = 1; i <= n; ++i)
        cin >> cost[i][0] >> cost[i][1] >> cost[i][2];

    int answer = INF;
    for (int st = 0; st < 3; ++st)
    {
        memset(dp, INF, sizeof(dp)); // 로직상 없어도 잘 동작하기는 하지만 명확하게 하자

        dp[1][st] = cost[1][st];
        for (int i = 2; i <= n; ++i)
        {
            dp[i][0] = cost[i][0] + min(dp[i-1][1], dp[i-1][2]);
            dp[i][1] = cost[i][1] + min(dp[i-1][0], dp[i-1][2]);
            dp[i][2] = cost[i][2] + min(dp[i-1][0], dp[i-1][1]);
        }

        for (int i = 0; i < 3; ++i)
        {
            if (i == st) continue;
            answer = min(answer, dp[n][i]);
        }
    }
    cout << answer;
}
