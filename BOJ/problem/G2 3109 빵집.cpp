// URL: https://www.acmicpc.net/problem/3109
// Algo: 그리디, DFS

// Start:	240605 07 02
// Read:	0 1
// Think:	0 2
// Code:	0 6
// Total:	0 9

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) x.begin(), x.end()
#define pb push_back

int dy[3] = {-1, 0, 1};
int n, m;
char board[10'000][500];
bool OOB(int y, int x) { return y < 0 || y >= n || x < 0 || x >= m; }

bool DFS(int y, int x)
{
    if (OOB(y, x) || board[y][x] != '.') return false;
    if (x == m - 1)
    {
        board[y][x] = 'a';
        return true;
    }

    bool success = false;
    for (const int d : dy)
    {
        success = DFS(y + d, x + 1);
        if (success) break;
    }

    if (!success)
    {
        board[y][x] = 'b';
        return false;
    }
    else
    {
        board[y][x] = 'a';
        return true;
    }
}

int main()
{
    fastio;
    cin >> n >> m;
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < m; ++j)
        {
            cin >> board[i][j];
        }
    }

    int answer = 0;
    for (int i = 0; i < n; ++i)
    {
        answer += DFS(i, 0);
    }

    cout << answer;
}
