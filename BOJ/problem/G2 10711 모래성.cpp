// URL: https://www.acmicpc.net/problem/10711
// Algo: BFS

// Start:	241014 21 36
// Read:	0 2
// Think:	0 2
// Code:	0 13
// Total:	0 17

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) x.begin(), x.end()
#define pb push_back

using pii = pair<int, int>;

int n, m;
int dy[8] = {1, 1, 1, 0, 0, -1, -1, -1};
int dx[8] = {1, 0, -1, 1, -1, 1, 0, -1};
inline bool OOB(int y, int x) { return y < 0 || y >= n || x < 0 || x >= m; }

char board[1'000][1'000];

int main()
{
    fastio;

    cin >> n >> m;

    queue<pii> q;
    for (int y = 0; y < n; ++y)
    {
        for (int x = 0; x < m; ++x)
        {
            char c;
            cin >> c;
            if (c == '.')
            {
                board[y][x] = 0;
                q.push({y, x});
            }
            else
            {
                board[y][x] = c - '0';
            }
        }
    }

    int wave = 0;
    while (!q.empty())
    {
        ++wave;
        int qsz = q.size();
        while (qsz--)
        {
            const auto [y, x] = q.front();
            q.pop();

            for (int i = 0; i < 8; ++i)
            {
                const int ny = y + dy[i];
                const int nx = x + dx[i];
                if (OOB(ny, nx) || board[ny][nx] == 0) continue;
                --board[ny][nx];
                if (board[ny][nx] == 0) q.push({ny, nx});
            }
        }
    }
    cout << wave - 1;
}
