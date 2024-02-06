// URL: https://www.acmicpc.net/problem/1753
// Algo: 다익스트라 기본

// Start:	240206 17 25
// Read:	17 26
// Think:	17 46  복습
// Code:	18 10
// Total:	0 45

#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define X first
#define Y second
#define all(x) x.begin(), x.end()
#define sortvec(x) sort(all(x))
#define compress(x) x.erase(unique(all(x)), x.end())
#define findvec(x, value) find(all(x), value) != x.end()

using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;

const ll  MOD = 1000000007;
const int INF = 0x3f3f3f3f;
const ll  LLINF = 1e18;


vector<pii> adj[20001]; // [비용, 도착정점]
int         d[20001]; // 최단거리

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int V, E, K;
    cin >> V >> E >> K;
    fill(d, d + V + 1, INF);

    while (E--)
    {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].pb({w, v}); // 실수: 비용 w, 노드 v로 적어야함. 반대로 적음
    }

    // 오름차순할땐 greater
    priority_queue<pii, vector<pii>, greater<>> pq;

    d[K] = 0;
    pq.push({d[K], K});

    while (!pq.empty())
    {
        auto [dist, node] = pq.top();
        pq.pop();

        if (d[node] != dist) continue;
        for (auto [nxtDist, nxtNode] : adj[node])
        {
            if (d[nxtNode] <= d[node] + nxtDist) continue;
            d[nxtNode] = d[node] + nxtDist;
            pq.push({d[nxtNode], nxtNode});
        }
    }

    // printing
    for (int i = 1; i <= V; ++i)
    {
        int dist = d[i];
        if (dist == INF) cout << "INF\n";
        else cout << dist << "\n";
    }
}
