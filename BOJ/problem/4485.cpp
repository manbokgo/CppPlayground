// 다익스트라
#include <bits/stdc++.h>
using namespace std;

int adj[125][125];
const int INF = 10000;

struct point {
    int x, y, c;
    bool operator<(point a) const { return c > a.c; }
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int dx[4] = {0, 0, 1, -1};
    int dy[4] = {1, -1, 0, 0};

    for (int t = 1;;++t)
    {
        int n;
        cin >> n;

        if (n == 0)
            return 0;

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                cin >> adj[i][j];
            }
        }

        int dist[n][n];
        fill(*dist, *dist + n * n, INF);
        bool visit[n][n];
        fill(*visit, *visit + n * n, false);
        priority_queue<point> PQ;

        dist[0][0] = adj[0][0];
        PQ.push({0, 0, dist[0][0]});

        while (!PQ.empty())
        {
            point cur;
            do
            {
                cur = PQ.top();
                PQ.pop();
            } while (!PQ.empty() && visit[cur.y][cur.x]);

            if (visit[cur.y][cur.x])
                break;

            visit[cur.y][cur.x] = true;
            for (int i = 0; i < 4; i++)
            {
                int y = cur.y + dy[i];
                int x = cur.x + dx[i];
                if (x < 0 || x >= n || y < 0 || y >= n)
                    continue;

                if (dist[cur.y][cur.x] + adj[y][x] < dist[y][x])
                {
                    dist[y][x] = dist[cur.y][cur.x] + adj[y][x];
                    PQ.push({x, y, dist[y][x]});
                }
            }
        }

        cout << "Problem " << t << ": " << dist[n - 1][n - 1] << "\n";
    }
}