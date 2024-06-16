// URL: https://www.acmicpc.net/problem/1987
// Algo: 백트래킹

// Start:	240616 14 03
// Read:	0 1
// Think:	0 0
// Code:	0 5
// Total:	0 6

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) x.begin(), x.end()
#define pb push_back

int n, m;
int dy[4] = {0, 1, 0, -1};
int dx[4] = {1, 0, -1, 0}; // 동남서북
bool OOB(int y, int x) { return y < 0 || y >= n || x < 0 || x >= m; }
bool visited[26];
char board[20][20];
int answer = 0;

void DFS(int y, int x, int sum)
{
    if (answer < sum) answer = sum;

    for (int i = 0; i < 4; ++i)
    {
        int ny = y + dy[i];
        int nx = x + dx[i];
        if (OOB(ny,nx) || visited[board[ny][nx] - 'A']) continue;

        visited[board[ny][nx] - 'A'] = true;
        DFS(ny, nx, sum + 1);
        visited[board[ny][nx] - 'A'] = false;
    }
}

int main()
{
    fastio;
    cin >> n >> m;
    for (int y = 0; y < n; ++y)
    {
        for (int x = 0; x < m; ++x)
        {
            cin >> board[y][x];
        }
    }

    visited[board[0][0] - 'A'] = true;
    DFS(0, 0, 1);
    cout << answer;
}
