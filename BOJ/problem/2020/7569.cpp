#include <bits/stdc++.h>
using namespace std;
#define mp make_pair

struct Tomato{
    int y, x, z;
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, h;
    cin >> m >> n >> h;
    int adj[n][m][h];
    int dx[6] = {1, -1, 0, 0, 0, 0};
    int dy[6] = {0, 0, 1, -1, 0, 0};
    int dz[6] = {0, 0, 0, 0, 1, -1};
    queue<Tomato> Q;

    for (int k = 0; k < h; k++)
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                cin >> adj[i][j][k];
                if (adj[i][j][k] == 1)
                    Q.push({i, j, k});
            }
        }
    }

    int num = 0;

    while (!Q.empty())
    {
        auto cur = Q.front();
        Q.pop();
        for (int k = 0; k < 6; k++)
        {
            int y = cur.y + dy[k];
            int x = cur.x + dx[k];
            int z = cur.z + dz[k];
            if (x < 0 || x >= m || y < 0 || y >= n || z < 0 || z >= h)
                continue;

            if (adj[y][x][z] == 0)
            {
                adj[y][x][z] = adj[cur.y][cur.x][cur.z] + 1;
                Q.push({y, x, z});
            }
        }
    }

    for (int k = 0; k < h; k++)
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                if (adj[i][j][k] == 0)
                {
                    cout << -1;
                    return 0;
                }
                num = max(num, adj[i][j][k]);
            }
            
        }
    }
    cout << num - 1;
}