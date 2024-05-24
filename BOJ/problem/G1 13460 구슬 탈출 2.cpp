// URL: https://www.acmicpc.net/problem/13460
// Algo: 시뮬레이션, BFS

// Start:	240525 00 28
// Read:	0 2
// Think:	0 5
// Code:	0 41
// Total:	0 48

// redVisit, blueVisit를 따로 두고, 둘 다 이미 방문했다면 큐에 집어넣지 않는 식으로 했다가 20분 헤맸다.
// 통합된 visited 배열을 4차원 배열로 두어서, 'red 위치에 따른 blue 위치의 상태'로 체크해야 함. 멍청함.

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) x.begin(), x.end()
#define pb push_back

constexpr int INF = 0x3f3f3f3f;

using pii = pair<int, int>;
using tiiii = tuple<int, int, int, int>;


int dy[4] = {0, 1, 0, -1};
int dx[4] = {1, 0, -1, 0}; // 동남서북

int tile[10][10];
bool visited[10][10][10][10]; // ry rx by bx
int main()
{
    fastio;

    int n, m;
    cin >> n >> m;

    tiiii pos;
    {
        auto& [ry, rx, by, bx] = pos;
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < m; ++j)
            {
                char c;
                cin >> c;
                switch (c)
                {
                case '#':
                    tile[i][j] = -1;
                    break;
                case 'O':
                    tile[i][j] = INF;
                    break;
                case 'R':
                    ry = i;
                    rx = j;
                    break;
                case 'B':
                    by = i;
                    bx = j;
                    break;
                default: ;
                }
            }
        }
        visited[ry][rx][by][bx] = true;
    }

    queue<tiiii> q;
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
                        if (tile[nry][nrx] == -1)
                        {
                            nry -= dy[i];
                            nrx -= dx[i];
                            rStuck = true;
                        }
                        else if (tile[nry][nrx] == INF)
                        {
                            rStuck = true;
                            rExit = true;
                        }
                    }

                    if (!bStuck)
                    {
                        nby += dy[i];
                        nbx += dx[i];
                        if (tile[nby][nbx] == -1)
                        {
                            nby -= dy[i];
                            nbx -= dx[i];
                            bStuck = true;
                        }
                        else if (tile[nby][nbx] == INF)
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
        if (cnt > 10)
            break;
    }

    cout << -1;
    return 0;
}
