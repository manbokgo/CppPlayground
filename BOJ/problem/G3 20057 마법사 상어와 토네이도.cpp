// URL: https://www.acmicpc.net/problem/20057
// Algo: 시뮬레이션

// Start:	240628 19 09
// Read:	0 2
// Think:	0 3
// Code:	0 28
// Total:	0 33

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) x.begin(), x.end()
#define pb push_back

using ll = long long;

int n;
int dy[4] = {0, 1, 0, -1};
int dx[4] = {-1, 0, 1, 0}; // 서남동북

int lry[2][2] = {{1, -1}, {0, 0}};
int lrx[2][2] = {{0, 0}, {1, -1}};

bool OOB(int y, int x) { return y < 0 || y >= n || x < 0 || x >= n; }

int board[499][499];

int main()
{
    fastio;
    cin >> n;
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            cin >> board[i][j];
        }
    }

    int move = 1;
    int dir = 0;
    int dirCnt = 0;

    int cy = n / 2;
    int cx = n / 2;

    int answer = 0;
    while (true)
    {
        if (cx < 0) break;

        const int lrIdx = dir % 2;
        for (int mv = 0; mv < move; ++mv)
        {
            const int ny = cy + dy[dir];
            const int nx = cx + dx[dir];

            int remain = board[ny][nx];

            // spread
            {
                // 5%
                if (const int subt = board[ny][nx] / 20)
                {
                    const int ty = ny + dy[dir] * 2;
                    const int tx = nx + dx[dir] * 2;

                    if (OOB(ty, tx)) answer += subt;
                    else board[ty][tx] += subt;

                    remain -= subt;
                }

                // 10%
                if (const int subt = board[ny][nx] / 10)
                {
                    for (int i = 0; i < 2; ++i)
                    {
                        const int ty = ny + dy[dir] + lry[lrIdx][i];
                        const int tx = nx + dx[dir] + lrx[lrIdx][i];

                        if (OOB(ty, tx)) answer += subt;
                        else board[ty][tx] += subt;

                        remain -= subt;
                    }
                }

                // 7%
                if (const int subt = board[ny][nx] * 0.07f)
                {
                    for (int i = 0; i < 2; ++i)
                    {
                        const int ty = ny + lry[lrIdx][i];
                        const int tx = nx + lrx[lrIdx][i];

                        if (OOB(ty, tx)) answer += subt;
                        else board[ty][tx] += subt;

                        remain -= subt;
                    }
                }

                // 2%
                if (const int subt = board[ny][nx] / 50)
                {
                    for (int i = 0; i < 2; ++i)
                    {
                        const int ty = ny + lry[lrIdx][i] * 2;
                        const int tx = nx + lrx[lrIdx][i] * 2;

                        if (OOB(ty, tx)) answer += subt;
                        else board[ty][tx] += subt;

                        remain -= subt;
                    }
                }

                // 1%
                if (const int subt = board[ny][nx] / 100)
                {
                    for (int i = 0; i < 2; ++i)
                    {
                        const int ty = cy + lry[lrIdx][i];
                        const int tx = cx + lrx[lrIdx][i];

                        if (OOB(ty, tx)) answer += subt;
                        else board[ty][tx] += subt;

                        remain -= subt;
                    }
                }

                // remain
                {
                    const int ty = ny + dy[dir];
                    const int tx = nx + dx[dir];

                    if (OOB(ty, tx)) answer += remain;
                    else board[ty][tx] += remain;
                }
            }

            board[ny][nx] = 0;
            cy = ny;
            cx = nx;
        }

        dir = (dir + 1) % 4;
        ++dirCnt;
        if (dirCnt == 2)
        {
            dirCnt = 0;
            ++move;
        }
    }

    cout << answer;
}
