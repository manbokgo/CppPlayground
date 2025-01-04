// URL: https://www.acmicpc.net/problem/1149
// Algo: DP

// Start:	250105 06 14
// Read:	0 1
// Think:	0 3
// Code:	0 3
// Total:	0 7

// G4 17404 RGB거리 2를 이미 풀어서 쉬운 문제다.
// 1번째 집과 n번째 집의 색이 달라야한다는 조건이 없어진만큼 복잡할 거 없이
// i번째 집을 c로 칠했을 때, 그 때까지의 최소 비용이라는 dp의 의미를 그대로 사용하여
// 그대로 n번째 dp를 구하면 된다.

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) x.begin(), x.end()
#define pb push_back

constexpr int INF = 0x3f3f3f3f;

int n;
int dp[1'001][3]; // i번째 집을 c로 칠했을 때, 그 때까지의 최소 비용

int main()
{
    fastio;
    cin >> n;

    int cost[3];
    for (int i = 1; i <= n; ++i)
    {
        cin >> cost[0] >> cost[1] >> cost[2];
        dp[i][0] = cost[0] + min(dp[i - 1][1], dp[i - 1][2]);
        dp[i][1] = cost[1] + min(dp[i - 1][0], dp[i - 1][2]);
        dp[i][2] = cost[2] + min(dp[i - 1][0], dp[i - 1][1]);
    }

    cout << min({dp[n][0], dp[n][1], dp[n][2]});
}
