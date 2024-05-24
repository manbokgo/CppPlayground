// URL: https://www.acmicpc.net/problem/15653
// Algo: 시뮬레이션, BFS

// Start:	240525 02 13
// Read:	0 1
// Think:	0 0
// Code:	0 0
// Total:	0 1

// G1 13460 구슬 탈출 2 복붙 날먹

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);

struct bInfo
{
    int ry;
    int rx;
    int by;
    int bx;
};

int dy[4] = {0, 1, 0, -1};
int dx[4] = {1, 0, -1, 0}; // 동남서북

char tile[10][10];
bool visited[10][10][10][10]; // ry rx by bx

int main()
{
    fastio;

    int n, m;
    cin >> n >> m;

    bInfo pos;
    {
        auto& [ry, rx, by, bx] = pos;
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < m; ++j)
            {
                cin >> tile[i][j];
                if (tile[i][j] == 'R')
                {
                    ry = i;
                    rx = j;
                }
                else if (tile[i][j] == 'B')
                {
                    by = i;
                    bx = j;
                }
            }
        }
        visited[ry][rx][by][bx] = true;
    }

    queue<bInfo> q;
    q.push(pos);

    int cnt = 1;
    while (!q.empty())
    {
        int qsz = q.size();
        while (qsz--)
        {
            const auto [ry, rx, by, bx] = q.front();
            q.pop();

            for (int i = 0; i < 4; ++i)
            {
                int nry = ry;
                int nrx = rx;
                int nby = by;
                int nbx = bx;

                bool rStuck = false;
                bool bStuck = false;
                bool rExit = false;
                bool bExit = false;
                while (!rStuck || !bStuck)
                {
                    if (!rStuck)
                    {
                        nry += dy[i];
                        nrx += dx[i];
                        if (tile[nry][nrx] == '#')
                        {
                            nry -= dy[i];
                            nrx -= dx[i];
                            rStuck = true;
                        }
                        else if (tile[nry][nrx] == 'O')
                        {
                            rStuck = true;
                            rExit = true;
                        }
                    }

                    if (!bStuck)
                    {
                        nby += dy[i];
                        nbx += dx[i];
                        if (tile[nby][nbx] == '#')
                        {
                            nby -= dy[i];
                            nbx -= dx[i];
                            bStuck = true;
                        }
                        else if (tile[nby][nbx] == 'O')
                        {
                            bStuck = true;
                            bExit = true;
                        }
                    }

                    if (nry == nby && nrx == nbx)
                    {
                        if (bStuck)
                        {
                            nry -= dy[i];
                            nrx -= dx[i];
                            rStuck = true;
                        }
                        else if (rStuck)
                        {
                            nby -= dy[i];
                            nbx -= dx[i];
                            bStuck = true;
                        }
                    }
                }

                if (bExit)
                {
                    continue;
                }
                if (rExit)
                {
                    cout << cnt;
                    return 0;
                }

                if (!visited[nry][nrx][nby][nbx])
                {
                    visited[nry][nrx][nby][nbx] = true;
                    q.push({nry, nrx, nby, nbx});
                }
            }
        }
        ++cnt;
    }

    cout << -1;
    return 0;
}
