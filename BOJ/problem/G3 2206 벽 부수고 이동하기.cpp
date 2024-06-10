// URL: https://www.acmicpc.net/problem/2206
// Algo: BFS

// Start:	240611 08 06
// Read:	0 1
// Think:	0 4
// Code:	0 9
// Total:	0 14

// LV3 67259 경주로 건설 문제와 비슷하다. 한 타일당 4방향 중 어느 방향으로 진입했는지를 각각 visited를 둔 거처럼
// visited에 차원을 하나 더 추가해서 체크해야 하는 문제

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) x.begin(), x.end()
#define pb push_back

using tiib = tuple<int, int, bool>;

int n, m;
char board[1'000][1'000];
bool visited[1'000][1'000][2]; // 부수기 전 방문, 부순 후방문

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
            board[y][x] -= '0';
        }
    }

    queue<tiib> q;
    visited[0][0][0] = true;
    q.push({0, 0, false});

    int cnt = 1;
    while (!q.empty())
    {
        int qsz = q.size();
        while (qsz--)
        {
            auto [y, x, broke] = q.front();
            q.pop();

            if (y == n - 1 && x == m - 1)
            {
                cout << cnt;
                return 0;
            }

            for (int i = 0; i < 4; ++i)
            {
                int ny = y + dy[i];
                int nx = x + dx[i];
                if (OOB(ny, nx) || visited[ny][nx][broke]) continue;
                if (board[ny][nx] == 1 && broke) continue;

                visited[ny][nx][broke] = true;
                q.push({ny, nx, broke | board[ny][nx]});
            }
        }
        ++cnt;
    }

    cout << -1;
}
