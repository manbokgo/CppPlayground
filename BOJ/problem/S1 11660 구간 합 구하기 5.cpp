// URL: https://www.acmicpc.net/problem/11660
// Algo: 누적 합

// Start:	250112 11 45
// Read:	0 1
// Think:	0 1
// Code:	0 5
// Total:	0 7

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) x.begin(), x.end()
#define pb push_back

int dp[1025][1025];

int main()
{
    fastio;

    int n, m;
    cin >> n >> m;

    for (int y = 1; y <= n; ++y)
    {
        for (int x = 1; x <= n; ++x)
        {
            int num;
            cin >> num;
            dp[y][x] = num + dp[y - 1][x] + dp[y][x - 1] - dp[y - 1][x - 1];
        }
    }

    while (m--)
    {
        int y1, x1, y2, x2;
        cin >> y1 >> x1 >> y2 >> x2;

        const int answer = dp[y2][x2] - dp[y2][x1 - 1] - dp[y1 - 1][x2] + dp[y1 - 1][x1 - 1];
        cout << answer << '\n';
    }
}
