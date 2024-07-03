// URL: https://www.acmicpc.net/problem/11562
// Algo: 플로이드

// Start:	240703 18 52
// Read:	0 3
// Think:	0 8
// Code:	0 4
// Total:	0 15

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) x.begin(), x.end()
#define pb push_back

constexpr int INF = 0x3f3f3f3f;

int dist[251][251];

int main()
{
    fastio;
    memset(dist, INF, sizeof(dist));

    int n, m;
    cin >> n >> m;

    while (m--)
    {
        int a, b, c;
        cin >> a >> b >> c;
        dist[a][b] = 0;
        dist[b][a] = c ? 0 : 1;
    }

    for (int k = 1; k <= n; ++k)
    {
        dist[k][k] = 0;
        for (int i = 1; i <= n; ++i)
        {
            for (int j = 1; j <= n; ++j)
            {
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }

    int T;
    cin >> T;
    while (T--)
    {
        int a, b;
        cin >> a >> b;
        cout << dist[a][b] << '\n';
    }
}
