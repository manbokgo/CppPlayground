#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define mp make_pair

const int MAX = 100;
int graph[MAX][MAX];
bool visit[MAX][MAX];
int dx[4] = {0, 0, 1, -1};
int dy[4] = {1, -1, 0, 0};

int main()
{
    int n, m;
    scanf("%d %d", &n, &m);

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            scanf("%1d", &graph[i][j]);
        }
    }

    queue<pair<int, int>> Q;
    Q.push(mp(0, 0));
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
            if (!visit[y][x] && graph[y][x] > 0)
            {
                visit[y][x] = true;
                if (y == n - 1 && x == m - 1)
                {
                    printf("%d", graph[cur.first][cur.second] + 1);
                    return 0;
                }
                graph[y][x] = graph[cur.first][cur.second] + 1;
                Q.push(mp(y, x));
            }
        }
    }
}