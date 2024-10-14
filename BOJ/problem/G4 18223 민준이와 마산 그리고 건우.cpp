// URL: https://www.acmicpc.net/problem/18223
// Algo: 다익스트라

// Start:	241015 07 30
// Read:	0 1
// Think:	0 3
// Code:	0 6
// Total:	0 10

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) x.begin(), x.end()
#define pb push_back

using pii = pair<int, int>;
constexpr int INF = 0x3f3f3f3f;

int v, e, p;
vector<pii> adj[5'001];

vector<int> Dijkstra(int st)
{
    static priority_queue<pii, vector<pii>, greater<>> pq;

    vector<int> D(v + 1, INF);
    D[st] = 0;
    pq.push({0, st});

    while (!pq.empty())
    {
        const auto [dist, node] = pq.top();
        pq.pop();
        if (dist != D[node]) continue;
        for (const auto [nDist, nNode] : adj[node])
        {
            if (D[nNode] <= dist + nDist) continue;
            D[nNode] = dist + nDist;
            pq.push({D[nNode], nNode});
        }
    }

    return D;
}

int main()
{
    fastio;

    cin >> v >> e >> p;

    while (e--)
    {
        int a, b, c;
        cin >> a >> b >> c;
        adj[a].pb({c, b});
        adj[b].pb({c, a});
    }

    const auto st1 = Dijkstra(1);
    const auto stP = Dijkstra(p);

    if (st1[p] + stP[v] <= st1[v]) cout << "SAVE HIM";
    else cout << "GOOD BYE";
}
