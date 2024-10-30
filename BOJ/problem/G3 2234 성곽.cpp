// URL: https://www.acmicpc.net/problem/2234
// Algo: BFS, 비트마스킹

// Start:	241030 10 23
// Read:	0 2
// Think:	0 2
// Code:	0 20
// Total:	0 24

// n이랑 m 좀 순서대로 달라고!!

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) x.begin(), x.end()
#define pb push_back

using pii = pair<int, int>;

int n, m;

int dy[4] = {0, -1, 0, 1};
int dx[4] = {-1, 0, 1, 0}; // 서북동남
inline bool OOB(int y, int x) { return y < 0 || y >= n || x < 0 || x >= m; }

int board[50][50];
int visited[50][50];
int roomSz[2501];

int main()
{
    fastio;

    cin >> m >> n;

    for (int y = 0; y < n; ++y)
    {
        for (int x = 0; x < m; ++x)
        {
            cin >> board[y][x];
        }
    }

    int cnt = 0;
    int largestRoom = 0;
    for (int y = 0; y < n; ++y)
    {
        for (int x = 0; x < m; ++x)
        {
            if (!visited[y][x])
            {
                ++cnt;

                queue<pii> q;
                visited[y][x] = cnt;
                q.push({y, x});

                while (!q.empty())
                {
                    const auto [cy, cx] = q.front();
                    q.pop();
                    ++roomSz[cnt];

                    for (int i = 0; i < 4; ++i)
                    {
                        const int ny = cy + dy[i];
                        const int nx = cx + dx[i];
                        if (OOB(ny, nx) || visited[ny][nx]) continue;
                        if (board[cy][cx] & (1 << i)) continue;

                        visited[ny][nx] = cnt;
                        q.push({ny, nx});
                    }
                }

                largestRoom = max(largestRoom, roomSz[cnt]);
            }
        }
    }

    int largestRoom2 = 0;
    for (int y = 0; y < n; ++y)
    {
        for (int x = 0; x < m; ++x)
        {
            for (int i = 2; i < 4; ++i)
            {
                const int ny = y + dy[i];
                const int nx = x + dx[i];
                if (OOB(ny, nx) || visited[y][x] == visited[ny][nx]) continue;
                if ((board[y][x] & (1 << i)) == 0) continue;

                largestRoom2 = max(largestRoom2, roomSz[visited[y][x]] + roomSz[visited[ny][nx]]);
            }
        }
    }

    cout << cnt << '\n' << largestRoom << '\n' << largestRoom2;
}
