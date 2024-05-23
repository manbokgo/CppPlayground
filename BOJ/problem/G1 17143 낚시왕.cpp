// URL: https://www.acmicpc.net/problem/17143
// Algo: 시뮬레이션

// Start:	240523 18 47
// Read:	0 3
// Think:	0 6
// Code:	0 42
// Total:	0 51

// 별거아닌 로직 실수 계속 남발해서 시간 엄청 걸렸다. 복잡한 시뮬레이션이라 디버깅도 어려웠음.

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) x.begin(), x.end()
#define pb push_back

struct shark
{
    int s;
    int d; // 1북 2남 3동 4서
    int z;
};


int n, m, shkCnt;
int dy[5] = {0, -1, 1, 0, 0};
int dx[5] = {0, 0, 0, 1, -1}; // X북남동서
int RevDir(int dir) { return dir % 2 ? dir + 1 : dir - 1; }

shark sharks[10001];
int tile[101][101]; // x, y
int tmp[101][101]; // x, y

int main()
{
    fastio;
    cin >> n >> m >> shkCnt;

    for (int i = 1; i <= shkCnt; ++i)
    {
        int y, x, s, d, z;
        cin >> y >> x >> s >> d >> z;
        sharks[i] = {s, d, z};
        tile[x][y] = i;
    }

    int answer = 0;
    for (int i = 1; i <= m; ++i)
    {
        // Fish
        for (int j = 1; j <= n; ++j)
        {
            if (!tile[i][j]) continue;
            answer += sharks[tile[i][j]].z;
            tile[i][j] = 0;
            break;
        }

        // Move
        memset(tmp, 0, sizeof(tmp));
        for (int x = 1; x <= m; ++x)
        {
            for (int y = 1; y <= n; ++y)
            {
                if (!tile[x][y]) continue;
                auto& [s, d, z] = sharks[tile[x][y]];

                int ny = y;
                int nx = x;

                if (d == 1 || d == 2)
                {
                    const int mCnt = s % ((n - 1) * 2);
                    ny += dy[d] * mCnt;

                    if (ny <= 0 || ny > n)
                    {
                        const int exceed = ny <= 0 ? 1 - ny : ny - n;
                        const int hit = exceed / (n - 1);
                        const int remain = exceed % (n - 1);

                        if ((ny <= 0 && hit) || (ny > n && !hit))
                        {
                            d = 1;
                            ny = n - remain;
                        }
                        else
                        {
                            d = 2;
                            ny = 1 + remain;
                        }
                    }
                }
                else
                {
                    const int mCnt = s % ((m - 1) * 2);
                    nx += dx[d] * mCnt;

                    if (nx <= 0 || nx > m)
                    {
                        const int exceed = nx <= 0 ? 1 - nx : nx - m;
                        const int hit = exceed / (m - 1);
                        const int remain = exceed % (m - 1);

                        if ((nx <= 0 && hit) || (nx > m && !hit))
                        {
                            d = 4;
                            nx = m - remain;
                        }
                        else
                        {
                            d = 3;
                            nx = 1 + remain;
                        }
                    }
                }

                if (!tmp[nx][ny] || z > sharks[tmp[nx][ny]].z)
                {
                    tmp[nx][ny] = tile[x][y];
                }
            }
        }

        // Update
        memcpy(tile, tmp, sizeof(tmp));
    }

    cout << answer;
}
