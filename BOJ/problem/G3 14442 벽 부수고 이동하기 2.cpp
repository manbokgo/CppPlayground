// URL: https://www.acmicpc.net/problem/14442
// Algo: BFS

// Start:	241008 18 48
// Read:	0 1
// Think:	0 2
// Code:	0 5
// Total:	0 8

// G3 2206 벽 부수고 이동하기 문제에서 visited 배열의 3번째 차원만 약간 변형된 문제다.

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) x.begin(), x.end()
#define pb push_back

using tiii = tuple<int, int, int>;

int n, m, k;
char board[1'000][1'000];
bool visited[1'000][1'000][10]; // 부수기 전 방문, 부순 후방문

int dy[4] = {0, 1, 0, -1};
int dx[4] = {1, 0, -1, 0}; // 동남서북
bool OOB(int y, int x) { return y < 0 || y >= n || x < 0 || x >= m; }

int main()
{
    fastio;

    cin >> n >> m >> k;
    for (int y = 0; y < n; ++y)
    {
        for (int x = 0; x < m; ++x)
        {
            cin >> board[y][x];
            board[y][x] -= '0';
        }
    }

    queue<tiii> q;
    visited[0][0][0] = true;
    q.push({0, 0, 0});

    int cnt = 1;
    while (!q.empty())
    {
        int qsz = q.size();
        while (qsz--)
        {
            const auto [y, x, broke] = q.front();
            q.pop();

            if (y == n - 1 && x == m - 1)
            {
                cout << cnt;
                return 0;
            }

            for (int i = 0; i < 4; ++i)
            {
                const int ny = y + dy[i];
                const int nx = x + dx[i];
                if (OOB(ny, nx)) continue;

                const int nBroke = broke + board[ny][nx];
                if (nBroke > k || visited[ny][nx][nBroke]) continue;

                visited[ny][nx][nBroke] = true;
                q.push({ny, nx, nBroke});
            }
        }
        ++cnt;
    }

    cout << -1;
}
