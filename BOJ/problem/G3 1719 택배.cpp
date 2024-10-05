// URL: https://www.acmicpc.net/problem/1719
// Algo: 플로이드 + 경로 복원 기본

// Start:	241005 16 20
// Read:	0 1
// Think:	0 1
// Code:	0 4
// Total:	0 6

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) x.begin(), x.end()
#define pb push_back

constexpr int INF = 0x3f3f3f3f;

int dist[201][201];
int nxt[201][201];

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
        dist[b][a] = min(dist[b][a], c);
        nxt[a][b] = b;
        nxt[b][a] = a;
    }

    // 플로이드 + 경로 복원
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
            if (s == e) cout << "- ";
            else cout << nxt[s][e] << " ";
        }
        cout << "\n";
    }
}
