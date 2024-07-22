// URL: https://www.acmicpc.net/problem/14863
// Algo: DP

// Start:	240722 14 56
// Read:	0 2
// Think:	0 16
// Code:	0 10
// Total:	0 28

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) x.begin(), x.end()
#define pb push_back

constexpr int INF = 0x3f3f3f3f;

using ti4 = tuple<int, int, int, int>;

int n, k;
ti4 routes[100];
int dp[100][100'001];

int Solve(int cur, int left)
{
    if (left < 0) return -INF;
    if (cur == n) return 0;
    if (dp[cur][left] != -1) return dp[cur][left];

    const auto [t1, m1, t2, m2] = routes[cur];
    return dp[cur][left] = max(
        Solve(cur + 1, left - t1) + m1,
        Solve(cur + 1, left - t2) + m2
    );
}

int main()
{
    fastio;
    memset(dp, -1, sizeof(dp));

    cin >> n >> k;
    for (int i = 0; i < n; ++i)
    {
        auto& [t1, m1, t2, m2] = routes[i];
        cin >> t1 >> m1 >> t2 >> m2;
    }

    cout << Solve(0, k);
}
