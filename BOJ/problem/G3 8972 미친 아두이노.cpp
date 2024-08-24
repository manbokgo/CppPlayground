// URL: https://www.acmicpc.net/problem/8972
// Algo: 시뮬레이션

// Start:	240824 13 14
// Read:	0 1
// Think:	0 2
// Code:	0 28
// Total:	0 31

// preBoard-board 구조, 겹치면 터지는 것 더 잘 생각하고 시작했어야 함. 좀 쓸데없이 약간 헤맨 듯.

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) x.begin(), x.end()
#define pb push_back

using pii = pair<int, int>;

int n, m;
int dy[10] = {0, 1, 1, 1, 0, 0, 0, -1, -1, -1};
int dx[10] = {0, -1, 0, 1, -1, 0, 1, -1, 0, 1};
bool OOB(int y, int x) { return y < 0 || y >= n || x < 0 || x >= m; }

char board[100][100];

int main()
{
    fastio;
    memset(board, '.', sizeof(board));
    cin >> n >> m;

    pii jong{};
    for (int y = 0; y < n; ++y)
    {
        for (int x = 0; x < m; ++x)
        {
            cin >> board[y][x];
            if (board[y][x] == 'I') jong = {y, x};
        }
    }

    string commands;
    cin >> commands;

    for (int cmdIdx = 0; cmdIdx < commands.size(); ++cmdIdx)
    {
        char preBoard[100][100];
        memcpy(preBoard, board, sizeof(preBoard));
        memset(board, '.', sizeof(board));

        const int cmd = commands[cmdIdx] - '0';
        auto& [jy, jx] = jong;

        jy += dy[cmd];
        jx += dx[cmd];
        if (preBoard[jy][jx] == 'R')
        {
            cout << "kraj " << cmdIdx + 1;
            return 0;
        }
        board[jy][jx] = 'I';

        for (int y = 0; y < n; ++y)
        {
            for (int x = 0; x < m; ++x)
            {
                if (preBoard[y][x] != 'R') continue;

                int ny = y;
                int nx = x;

                if (jy < y) --ny;
                else if (y < jy) ++ny;

                if (jx < x) --nx;
                else if (x < jx) ++nx;

                if (board[ny][nx] == 'I')
                {
                    cout << "kraj " << cmdIdx + 1;
                    return 0;
                }

                if (board[ny][nx] == 'R' || board[ny][nx] == 'X')
                    board[ny][nx] = 'X';
                else
                    board[ny][nx] = 'R';
            }
        }
    }

    for (int y = 0; y < n; ++y)
    {
        for (int x = 0; x < m; ++x)
        {
            if (board[y][x] == 'X') board[y][x] = '.';
            cout << board[y][x];
        }
        cout << '\n';
    }
}
