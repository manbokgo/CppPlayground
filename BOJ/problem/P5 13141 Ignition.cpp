// URL: https://www.acmicpc.net/problem/13141
// Algo: 플로이드

// Start:	240717 12 38
// Read:	0 3
// Think:	0 47
// Code:	0 11
// Total:   1 1

// 일단 플로이드를 돌린다. t 정점에 불을 붙인다고 했을 때, 모든 간선들 중 태워지는 시간이 가장 긴 것을 구해야 함.

// 어떤 간선의 길이가 c일 때, s 정점이 불붙은 후 e 정점이 불붙는 시간,
// 다시 말해 s와 e의 최단 거리인 dist[t][e] - dist[t][s]를 x라고 둔다면
// (여러 케이스 생각해보니 간선에서의 s와 e의 구분은 딱히 필요 없음.)

// x 시간 후에는 간선의 반대쪽 끝에 불이 붙어, 남은 길이가 2배 빨리 태워지게 되니
// 간선이 불태워지는 시간 자체는 (c - x) / 2 + x   =  (c + x) / 2 임

// 여기에 dist[t][s]를 더하면 t에서부터 시작해서 그 간선이 불타는 최종 시각을 구할 수 있다.
// (c + dist[t][e] - dist[t][s]) / 2 + dist[t][s] = (c + dist[t][e] + dist[t][s]) / 2
// 즉 (간선길이 + 시작점에서 s까지 최단거리 + 시작점에서 e까지의 최단거리의 합) / 2 이
// 그 간선이 태워지는 최종 시각이다. 이것이 가장 작은 걸 구하면 됨.

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) x.begin(), x.end()
#define pb push_back

constexpr int INF = 0x3f3f3f3f;
using tiii = tuple<int, int, int>;

int dist[201][201];
vector<tiii> adj;

int main()
{
    fastio;

    memset(dist, INF, sizeof(dist));

    int n, m;
    cin >> n >> m;
    adj.reserve(m);

    for (int i = 1; i <= n; ++i)
        dist[i][i] = 0;

    while (m--)
    {
        int a, b, c;
        cin >> a >> b >> c;
        c *= 2;

        dist[a][b] = min(dist[a][b], c);
        dist[b][a] = min(dist[b][a], c);
        adj.pb({a, b, c});
    }

    // 플로이드
    for (int k = 1; k <= n; ++k)
        for (int s = 1; s <= n; ++s)
            for (int e = 1; e <= n; ++e)
                dist[s][e] = min(dist[s][e], dist[s][k] + dist[k][e]);

    int answer = INF;
    for (int t = 1; t <= n; ++t)
    {
        int mxTime = 0;
        for (const auto [a, b, c] : adj)
            mxTime = max(mxTime, (c + dist[t][b] + dist[t][a]) / 2);

        answer = min(answer, mxTime);
    }

    cout.precision(1);
    cout << fixed << answer / 2.0;
}
