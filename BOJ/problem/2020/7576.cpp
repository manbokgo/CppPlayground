#include <bits/stdc++.h>
using namespace std;
#define mp make_pair

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> m >> n;
    int adj[n][m];
    int dx[4] = {0, 0, 1, -1};
    int dy[4] = {1, -1, 0, 0};
    queue<pair<int, int>> Q;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            int val;
            cin >> val;
            adj[i][j] = val;
            if (val == 1)
                Q.push(mp(i, j));
        }
    }

    int num = 0;

    while (!Q.empty())
    {
        auto cur = Q.front();
        Q.pop();
        for (int k = 0; k < 4; k++)
        {
            int y = cur.first + dy[k];
            int x = cur.second + dx[k];
            if (x < 0 || x >= m || y < 0 || y >= n)
                continue;

            if (adj[y][x] == 0)
            {
                adj[y][x] = adj[cur.first][cur.second] + 1;
                Q.push(mp(y, x));
            }
        }
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (adj[i][j] == 0)
            {
                cout << -1;
                return 0;
            }
            num = max(num, adj[i][j]);
        }
    }
    cout << num - 1;
}