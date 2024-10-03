// URL: https://www.acmicpc.net/problem/2151
// Algo: BFS

// Start:	241003 13 53
// Read:	0 2
// Think:	0 6
// Code:	0 29
// Total:	0 37

// G3 6087 레이저 통신과 비슷하다. 특정 타일을 얼만큼의 최소 직선으로 도달할 수 있냐를 묻는 문제.

// 지나가는 모든 타일에서, 모든 방향으로 뻗어나갈 수 있었던 것과 다르게,
// 거울이 놓일 수 있는 위치 '!'에서만 '좌우 방향으로만' 뻗어나갈 수 있다는 게 차이다.
// 따라서 큐에 진행 방향 정보 또한 있어야 한다.

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) x.begin(), x.end()
#define pb push_back

using pii = pair<int, int>;
using tiii = tuple<int, int, int>;

constexpr int INF = 0x3f3f3f3f;

int n;
int dy[4] = {0, 1, 0, -1};
int dx[4] = {1, 0, -1, 0}; // 동남서북
inline bool OOB(int y, int x) { return y < 0 || y >= n || x < 0 || x >= n; }

int board[50][50];

int main()
{
    fastio;
    memset(board, -1, sizeof(board));

    cin >> n;

    vector<pii> entrance;
    for (int y = 0; y < n; ++y)
    {
        for (int x = 0; x < n; ++x)
        {
            char c;
            cin >> c;
            if (c == '#') entrance.pb({y, x});
            if (c == '*') board[y][x] = INF;
            if (c == '!') board[y][x] = -2;
        }
    }

    queue<tiii> q;
    board[entrance[0].first][entrance[0].second] = 0;
    for (int i = 0; i < 4; ++i)
    {
        q.push({entrance[0].first, entrance[0].second, i});
    }

    while (!q.empty())
    {
        const auto [cy, cx, dir] = q.front();
        q.pop();

        int ny = cy + dy[dir];
        int nx = cx + dx[dir];

        while (!OOB(ny, nx) && board[ny][nx] != INF)
        {
            if (board[ny][nx] < 0)
            {
                if (board[ny][nx] == -2)
                {
                    const int rightDir = (dir + 1) % 4;
                    q.push({ny, nx, rightDir});

                    const int leftDir = (dir + 3) % 4;
                    q.push({ny, nx, leftDir});
                }

                board[ny][nx] = board[cy][cx] + 1;
            }

            ny += dy[dir];
            nx += dx[dir];
        }
    }

    cout << board[entrance[1].first][entrance[1].second] - 1;
}
