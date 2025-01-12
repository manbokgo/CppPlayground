// URL: https://www.acmicpc.net/problem/1932
// Algo: DP

// Start:	250113 08 04
// Read:	0 1
// Think:	0 4
// Code:	0 3
// Total:	0 8

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) x.begin(), x.end()
#define pb push_back

int dp[501][501];

int main()
{
    fastio;

    int n;
    cin >> n;

    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j <= i; ++j)
        {
            cin >> dp[i][j];
        }
    }

    for (int i = n - 1; i >= 1; --i)
    {
        for (int j = 0; j < i; ++j)
        {
            dp[i-1][j] += max(dp[i][j], dp[i][j+1]);
        }
    }

    cout << dp[0][0];
}
