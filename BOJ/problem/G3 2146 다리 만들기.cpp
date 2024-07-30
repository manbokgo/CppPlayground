// URL: https://www.acmicpc.net/problem/2146
// Algo: BFS

// Start:	240730 17 56
// Read:	0 2
// Think:	0 5
// Code:	0 11
// Total:	0 18

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) x.begin(), x.end()
#define pb push_back

constexpr int INF = 0x3f3f3f3f;
using pii = pair<int, int>;

int dy[4] = {0, 1, 0, -1};
int dx[4] = {1, 0, -1, 0}; // 동남서북

int n;
int board[100][100];
int dist[100][100];

bool OOB(int y, int x) { return y < 0 || y >= n || x < 0 || x >= n; }

int main()
{
    fastio;

    cin >> n;
    for (int y = 0; y < n; ++y)
    {
        for (int x = 0; x < n; ++x)
        {
            cin >> board[y][x];
            if (board[y][x] == 1) board[y][x] = -1;
        }
    }

    int cnt = 0;
    for (int y = 0; y < n; ++y)
    {
        for (int x = 0; x < n; ++x)
        {
            if (board[y][x] == -1)
            {
                ++cnt;

                queue<pii> q;
                board[y][x] = cnt;
                q.push({y, x});

                while (!q.empty())
                {
                    const auto [cy, cx] = q.front();
                    q.pop();

                    for (int i = 0; i < 4; ++i)
                    {
                        const int ny = cy + dy[i];
                        const int nx = cx + dx[i];
                        if (OOB(ny, nx) || board[ny][nx] != -1) continue;

                        board[ny][nx] = cnt;
                        q.push({ny, nx});
                    }
                }
            }
        }
    }


    queue<pii> q;
    for (int y = 0; y < n; ++y)
    {
        for (int x = 0; x < n; ++x)
        {
            if (board[y][x] != 0)
            {
                q.push({y, x});
            }
        }
    }

    int answer = INF;
    while (!q.empty())
    {
        const auto [cy, cx] = q.front();
        q.pop();

        const int cur = board[cy][cx];
        for (int i = 0; i < 4; ++i)
        {
            const int ny = cy + dy[i];
            const int nx = cx + dx[i];
            if (OOB(ny, nx) || board[ny][nx] == cur) continue;
            if (board[ny][nx] != 0)
            {
                answer = min(answer, dist[ny][nx] + dist[cy][cx]);
                continue;
            }

            board[ny][nx] = cur;
            dist[ny][nx] = dist[cy][cx] + 1;
            q.push({ny, nx});
        }
    }

    cout << answer;
}
