// URL: https://www.acmicpc.net/problem/11780
// Algo: 플로이드 + 복원 기본

// Start:	241001 14 37
// Read:	0 1
// Think:	0 3
// Code:	0 7
// Total:	0 11

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) x.begin(), x.end()
#define pb push_back

constexpr int INF = 0x3f3f3f3f;

int dist[101][101];
int nxt[101][101];

int main()
{
    fastio;

    memset(dist, INF, sizeof(dist));

    int n, m;
    cin >> n >> m;

    for (int i = 1; i <= n; ++i)
        dist[i][i] = 0;

    while (m--)
    {
        int a, b, c;
        cin >> a >> b >> c;
        dist[a][b] = min(dist[a][b], c);
        nxt[a][b] = b;
    }

    // 플로이드 + 복원
    for (int k = 1; k <= n; ++k)
    {
        for (int s = 1; s <= n; ++s)
        {
            for (int e = 1; e <= n; ++e)
            {
                if (dist[s][e] <= dist[s][k] + dist[k][e]) continue;
                dist[s][e] = dist[s][k] + dist[k][e];
                nxt[s][e] = nxt[s][k];
            }
        }
    }

    for (int s = 1; s <= n; ++s)
    {
        for (int e = 1; e <= n; ++e)
        {
            if (dist[s][e] == INF) cout << "0 ";
            else cout << dist[s][e] << " ";
        }

        cout << "\n";
    }

    for (int s = 1; s <= n; ++s)
    {
        for (int e = 1; e <= n; ++e)
        {
            if (dist[s][e] == INF || dist[s][e] == 0)
            {
                cout << "0\n";
                continue;
            }

            vector<int> path;

            int cur = s;
            while (cur != e)
            {
                path.pb(cur);
                cur = nxt[cur][e];
            }
            path.pb(e);

            cout << path.size() << ' ';
            for (const int num : path) cout << num << ' ';
            cout << '\n';
        }
    }
}
