// URL: https://www.acmicpc.net/problem/10026
// Algo: DFS

// Start:	241115 07 34
// Read:	0 1
// Think:	0 1
// Code:	0 4
// Total:	0 6

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) x.begin(), x.end()
#define pb push_back

int n;
int dy[4] = {0, 1, 0, -1};
int dx[4] = {1, 0, -1, 0}; // 동남서북
inline bool OOB(int y, int x) { return y < 0 || y >= n || x < 0 || x >= n; }

char board[100][100];
bool visited[100][100];

void DFS(int y, int x)
{
    visited[y][x] = true;
    for (int i = 0; i < 4; ++i)
    {
        const int ny = y + dy[i];
        const int nx = x + dx[i];

        if (OOB(ny, nx) || visited[ny][nx]) continue;
        if (board[y][x] != board[ny][nx]) continue;
        DFS(ny, nx);
    }
}

int main()
{
    fastio;

    cin >> n;
    for (int y = 0; y < n; ++y)
    {
        for (int x = 0; x < n; ++x)
        {
            cin >> board[y][x];
        }
    }

    int cntA = 0;
    for (int y = 0; y < n; ++y)
    {
        for (int x = 0; x < n; ++x)
        {
            if (visited[y][x]) continue;
            ++cntA;
            DFS(y, x);
        }
    }

    memset(visited, false, sizeof(visited));
    for (int y = 0; y < n; ++y)
    {
        for (int x = 0; x < n; ++x)
        {
            if (board[y][x] == 'G') board[y][x] = 'R';
        }
    }

    int cntB = 0;
    for (int y = 0; y < n; ++y)
    {
        for (int x = 0; x < n; ++x)
        {
            if (visited[y][x]) continue;
            ++cntB;
            DFS(y, x);
        }
    }

    cout << cntA << ' ' << cntB;
}
