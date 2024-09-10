// URL: https://www.acmicpc.net/problem/2458
// Algo: 플로이드

// Start:	240910 23 23
// Read:	0 1
// Think:	0 1
// Code:	0 11
// Total:   0 13

// LV3 49191 순위 문제와 거의 같다.
// 그 때처럼 dist를 bool 배열로 하지 않고, 일반적인 int 배열로 사용하여 좀 더 간단하게 했음

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) x.begin(), x.end()
#define pb push_back

constexpr int INF = 0x3f3f3f3f;
int dist[501][501];

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
        int a, b;
        cin >> a >> b;
        dist[a][b] = 1;
    }

    // 플로이드
    for (int k = 1; k <= n; ++k)
        for (int s = 1; s <= n; ++s)
            for (int e = 1; e <= n; ++e)
                dist[s][e] = min(dist[s][e], dist[s][k] + dist[k][e]);

    int answer = 0;
    for (int k = 1; k <= n; ++k)
    {
        bool found = true;
        for (int i = 1; i <= n; ++i)
        {
            if (dist[k][i] == INF && dist[i][k] == INF)
            {
                found = false;
                break;
            }
        }
        if (found) ++answer;
    }
    cout << answer;
}
