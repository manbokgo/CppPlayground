#include <bits/stdc++.h>
using namespace std;

int dp[1000][1000];
int graph[1000][1000];

int solve(int y, int x)
{
    if (x == 0 && y == 0)
        return graph[y][x];
    if (dp[y][x] != -1)
        return dp[y][x];

    if (y > 0)
        dp[y][x] = max(dp[y][x], solve(y - 1, x));
    if (x > 0)
        dp[y][x] = max(dp[y][x], solve(y, x - 1));
    if (y > 0 && x > 0)
        dp[y][x] = max(dp[y][x], solve(y - 1, x - 1));
    dp[y][x] += graph[y][x];

    return dp[y][x];
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    fill(*dp, *dp + sizeof(dp) / sizeof(int), -1);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cin >> graph[i][j];
        }
    }

    cout << solve(n -1, m - 1);
}