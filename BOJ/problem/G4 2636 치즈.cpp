// URL: https://www.acmicpc.net/problem/2636
// Algo: 시뮬레이션, BFS

// Start:	240808 07 34
// Read:	0 2
// Think:	0 2
// Code:	0 12
// Total:	0 16

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) x.begin(), x.end()
#define pb push_back

using pii = pair<int, int>;

int n, m;
bool board[100][100];
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

    // 치즈는 무조건 한 칸 이상 존재함
    int step = -1;
    int remain = -1;
    while (!q.empty())
    {
        ++step;
        remain = q.size();
        while (!q.empty())
        {
            const auto [cy, cx] = q.front();
            q.pop();

            for (int i = 0; i < 4; ++i)
            {
                const int ny = cy + dy[i];
                const int nx = cx + dx[i];
                if (OOB(ny, nx) || visited[ny][nx]) continue;
                visited[ny][nx] = true;

                if (!board[ny][nx]) q.push({ny, nx});
                else p.push({ny, nx});
            }
        }
        q.swap(p);
    }

    cout << step << '\n' << remain;
}
