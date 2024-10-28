// URL: https://www.acmicpc.net/problem/1865
// Algo: 벨만 포드

// Start:	241028 09 38
// Read:	0 3
// Think:	0 2
// Code:	0 15
// Total:	0 20

// 벨만 포드로 음수 사이클이 존재하는지'만' 확인하는 문제다.
// 백준이 음수 사이클에서 시작한다면 문제 조건을 충족한다.

// 특정 지점에서 시작하여 거리를 구하는 게 목적이 아니라
// 전체 그래프를 순회하다가 n번째 순회해서 갱신되는지만 보는게 중요하다.

// 거리 값을 구하는게 목적이 아니므로 fill_n(D, 501, INF); 는 필요 없다.
// D[1] = 0; 도 필요 없으며, 1과 연결된 지점들만 순회하는 if (D[a] == INF) continue; 을 지워서
// 모든 간선을 다 검사해야 한다.

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) x.begin(), x.end()
#define pb push_back

using tiii = tuple<int, int, int>;
using ll = long long;

constexpr int INF = 0x3f3f3f3f;

ll D[501];

bool Bellman(int n, const vector<tiii>& edges)
{
    // D[1] = 0;
    for (int i = 1; i <= n; ++i)
    {
        for (const auto& [a, b, c] : edges)
        {
            // if (D[a] == INF) continue;
            if (D[b] <= D[a] + c) continue;
            D[b] = D[a] + c;
            if (i == n) return true;
        }
    }
    return false;
}

int main()
{
    fastio;

    int T;
    cin >> T;

    while (T--)
    {
        fill_n(D, 501, 0);

        int n, m, w;
        cin >> n >> m >> w;

        vector<tiii> edges;
        for (int i = 0; i < m; ++i)
        {
            int a, b, c;
            cin >> a >> b >> c;
            edges.pb({a, b, c});
            edges.pb({b, a, c});
        }

        for (int i = 0; i < w; ++i)
        {
            int a, b, c;
            cin >> a >> b >> c;
            edges.pb({a, b, -c});
        }

        const bool isCycle = Bellman(n, edges);

        if (isCycle) cout << "YES\n";
        else cout << "NO\n";
    }
}
