// URL: https://www.acmicpc.net/problem/1956
// Algo: 플로이드 기본

// Start:	240808 09 00
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

int dist[401][401];

int main()
{
    fastio;
    memset(dist, INF, sizeof(dist));

    int n, m;
    cin >> n >> m;

    // 이거 안 하는게 핵심인 문제
    // for (int i = 1; i <= n; ++i)
    //     dist[i][i] = 0;

    while (m--)
    {
        int a, b, c;
        cin >> a >> b >> c;
        dist[a][b] = c;
    }

    for (int k = 1; k <= n; ++k)
        for (int s = 1; s <= n; ++s)
            for (int e = 1; e <= n; ++e)
                dist[s][e] = min(dist[s][e], dist[s][k] + dist[k][e]);

    int answer = INF;
    for (int i = 1; i <= n; ++i)
        answer = min(answer, dist[i][i]);

    if (answer == INF) cout << -1;
    else cout << answer;
}
