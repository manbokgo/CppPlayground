// URL: https://www.acmicpc.net/problem/1937
// Algo: DP, DFS

// Start:	240827 13 36
// Read:	0 1
// Think:	0 2
// Code:	0 5
// Total:	0 8

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) x.begin(), x.end()
#define pb push_back

int n;
int board[500][500];
int dp[500][500];

int dy[4] = {0, 1, 0, -1};
int dx[4] = {1, 0, -1, 0}; // 동남서북
bool OOB(int y, int x) { return y < 0 || y >= n || x < 0 || x >= n; }


int DFS(int y, int x)
{
    if (dp[y][x] != -1) return dp[y][x];

    dp[y][x] = 1;
    for (int i = 0; i < 4; ++i)
    {
        const int ny = y + dy[i];
        const int nx = x + dx[i];
        if (OOB(ny, nx)) continue;
        if (board[y][x] >= board[ny][nx]) continue;

        dp[y][x] = max(dp[y][x], DFS(ny, nx) + 1);
    }
    return dp[y][x];
}

int main()
{
    fastio;
    memset(dp, -1, sizeof(dp));

    cin >> n;
    for (int y = 0; y < n; ++y)
    {
        for (int x = 0; x < n; ++x)
        {
            cin >> board[y][x];
        }
    }

    int answer = 0;
    for (int y = 0; y < n; ++y)
    {
        for (int x = 0; x < n; ++x)
        {
            answer = max(answer, DFS(y, x));
        }
    }
    cout << answer;
}
