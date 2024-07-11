// URL: https://www.acmicpc.net/problem/1916
// Algo: 다익스트라 기본

// Start:	240712 07 37
// Read:	0 1
// Think:	0 0
// Code:	0 4
// Total:	0 5

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) x.begin(), x.end()
#define pb push_back

constexpr int INF = 0x3f3f3f3f;
using pii = pair<int, int>;

int D[1001];
vector<pii> adj[1001];

int main()
{
    fastio;

    memset(D, INF, sizeof(D));

    int n, m;
    cin >> n >> m;

    while (m--)
    {
        int a, b, c;
        cin >> a >> b >> c;
        adj[a].pb({c, b});
    }

    int st, en;
    cin >> st >> en;

    priority_queue<pii, vector<pii>, greater<>> pq;
    D[st] = 0;
    pq.push({D[st], st});

    while (!pq.empty())
    {
        auto [dist, node] = pq.top();
        pq.pop();

        if (dist != D[node]) continue;
        for (const auto [nDist, nNode] : adj[node])
        {
            if (D[nNode] <= dist + nDist) continue;
            D[nNode] = dist + nDist;
            pq.push({D[nNode], nNode});
        }
    }

    cout << D[en];
}
