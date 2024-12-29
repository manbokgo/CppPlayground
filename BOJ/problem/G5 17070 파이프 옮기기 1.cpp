// URL: https://www.acmicpc.net/problem/17070
// Algo: DP

// Start:	241229 22 52
// Read:	0 2
// Think:	0 5
// Code:	0 14
// Total:	0 21

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) x.begin(), x.end()
#define pb push_back

struct PipeState
{
    int horizon;
    int vertical;
    int diagonal;
};

PipeState dp[17][17];
int board[17][17];

int main()
{
    fastio;

    int n;
    cin >> n;

    for (int y = 1; y <= n; ++y)
    {
        for (int x = 1; x <= n; ++x)
        {
            cin >> board[y][x];
        }
    }

    dp[1][2].horizon = 1;
    for (int y = 1; y <= n; ++y)
    {
        for (int x = 3; x <= n; ++x)
        {
            if (board[y][x]) continue;

            dp[y][x].horizon = dp[y][x - 1].horizon + dp[y][x - 1].diagonal;
            dp[y][x].vertical = dp[y - 1][x].vertical + dp[y - 1][x].diagonal;
            if (!board[y - 1][x] && !board[y][x - 1])
                dp[y][x].diagonal = dp[y - 1][x - 1].horizon + dp[y - 1][x - 1].vertical + dp[y - 1][x - 1].diagonal;
        }
    }

    cout << dp[n][n].horizon + dp[n][n].vertical + dp[n][n].diagonal;
}
