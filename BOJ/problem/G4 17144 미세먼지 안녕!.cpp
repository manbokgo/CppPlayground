// URL: https://www.acmicpc.net/problem/17144
// Algo: 시뮬레이션

// Start:	240614 21 32
// Read:	0 3
// Think:	0 1
// Code:	0 15
// Total:	0 21

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) x.begin(), x.end()
#define pb push_back

constexpr int INF = 0x3f3f3f3f;

int n, m, t;
int o1, o2;
int dy[4] = {0, 1, 0, -1};
int dx[4] = {1, 0, -1, 0}; // 동남서북
bool OOB(int y, int x) { return y < 0 || y >= n || x < 0 || x >= m; }

int board[50][50];

int main()
{
    fastio;
    cin >> n >> m >> t;
    o1 = -1;
    o2 = -1;
    for (int y = 0; y < n; ++y)
    {
        for (int x = 0; x < m; ++x)
        {
            cin >> board[y][x];
            if (board[y][x] == -1)
            {
                if (o1 == -1) o1 = y;
                else if (o2 == -1) o2 = y;
            }
        }
    }


    while (t--)
    {
        // 확산
        int preBoard[50][50];
        memcpy(preBoard, board, sizeof(board));
        for (int y = 0; y < n; ++y)
        {
            for (int x = 0; x < m; ++x)
            {
                if (preBoard[y][x] <= 0) continue;
                const int spread = preBoard[y][x] / 5;
                for (int i = 0; i < 4; ++i)
                {
                    const int ny = y + dy[i];
                    const int nx = x + dx[i];
                    if (OOB(ny, nx) || preBoard[ny][nx] == -1) continue;
                    board[ny][nx] += spread;
                    board[y][x] -= spread;
                }
            }
        }

        // 순환
        board[o1 - 1][0] = 0;
        for (int y = o1 - 2; y >= 0; --y) board[y + 1][0] = board[y][0];
        for (int x = 1; x < m; ++x) board[0][x - 1] = board[0][x];
        for (int y = 1; y <= o1; ++y) board[y - 1][m - 1] = board[y][m - 1];
        for (int x = m - 2; x >= 1; --x) board[o1][x + 1] = board[o1][x];
        board[o1][1] = 0;

        board[o2 + 1][0] = 0;
        for (int y = o2 + 2; y < n; ++y) board[y - 1][0] = board[y][0];
        for (int x = 1; x < m; ++x) board[n - 1][x - 1] = board[n - 1][x];
        for (int y = n - 2; y >= o2; --y) board[y + 1][m - 1] = board[y][m - 1];
        for (int x = m - 2; x >= 1; --x) board[o2][x + 1] = board[o2][x];
        board[o2][1] = 0;
    }

    int answer = 0;
    for (int y = 0; y < n; ++y)
    {
        for (int x = 0; x < m; ++x)
        {
            if (board[y][x] > 0) answer += board[y][x];
        }
    }
    cout << answer;
}
