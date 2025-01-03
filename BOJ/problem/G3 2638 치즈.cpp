// URL: https://www.acmicpc.net/problem/2638
// Algo: 시뮬레이션, BFS

// Start:	250103 14 52
// Read:	0 1
// Think:	0 2
// Code:	0 25
// Total:	0 28

// G4 2636 치즈 문제와 비슷하지만, 단순히 외부 공기와 맞닿은 치즈를 제거하는 것이 아니라
// 최소 2개의 외부 공기와 맞닿은 치즈를 제거한다는 점이 다르다.

// 마찬가지로 q에는 이번 턴에 녹을 치즈와, 그 치즈들이 녹으면서 도달할 수 있게 되는 공기들을 넣고
// p에는 다음 턴에 녹을 치즈를 넣는다.

// 어떤 치즈가 외부 공기 2개와 맞닿았는지를 검사할 때
// 주변 공기가 visited 되어있다면 그 공기는 외부와 연결된 것이다.

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) x.begin(), x.end()
#define pb push_back

using pii = pair<int, int>;

int n, m;
int board[100][100];
bool visited[100][100];

int dy[4] = {0, 1, 0, -1};
int dx[4] = {1, 0, -1, 0}; // 동남서북
bool OOB(int y, int x) { return y < 0 || y >= n || x < 0 || x >= m; }

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

    queue<pii> q, p;
    visited[0][0] = true;
    q.push({0, 0});

    int step = -1;
    while (!q.empty())
    {
        ++step;
        while (!q.empty())
        {
            const auto [cy, cx] = q.front();
            q.pop();
            board[cy][cx] = false;

            for (int i = 0; i < 4; ++i)
            {
                const int ny = cy + dy[i];
                const int nx = cx + dx[i];
                if (OOB(ny, nx) || visited[ny][nx]) continue;

                if (!board[ny][nx])
                {
                    visited[ny][nx] = true;
                    q.push({ny, nx});
                    continue;
                }

                int expose = 0;
                for (int j = 0; j < 4; ++j)
                {
                    const int nnx = nx + dx[j];
                    const int nny = ny + dy[j];
                    if (OOB(nny, nnx)) continue;
                    if (!board[nny][nnx] && visited[nny][nnx]) // visited는 외부 공기와 연결되어 있음을 의미
                        ++expose;
                }
                if (expose < 2) continue;

                visited[ny][nx] = true;
                p.push({ny, nx});
            }
        }
        q.swap(p);
    }

    cout << step;
}
