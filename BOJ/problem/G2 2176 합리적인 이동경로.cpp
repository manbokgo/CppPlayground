// URL: https://www.acmicpc.net/problem/2176
// Algo: 다익스트라, DP, DFS

// Start:	240624 06 55
// Read:	0 3
// Think:	0 1
// Code:	0 15
// Total:	0 19

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) x.begin(), x.end()
#define pb push_back

constexpr int INF = 0x3f3f3f3f;
using pii = pair<int, int>;

int n, m;
vector<pii> adj[1'001];

int D[1'001];
int dp[1'001];

int DFS(int node)
{
    if (dp[node] != -1) return dp[node];

    dp[node] = 0;
    for (const auto [nDist, nNode] : adj[node])
    {
        if (D[node] <= D[nNode]) continue;
        dp[node] += DFS(nNode);
    }
    return dp[node];
}

int main()
{
    fastio;
    memset(D, INF, sizeof(D));
    memset(dp, -1, sizeof(dp));

    cin >> n >> m;
    while (m--)
    {
        int a, b, c;
        cin >> a >> b >> c;
        adj[a].pb({c, b});
        adj[b].pb({c, a});
    }

    priority_queue<pii, vector<pii>, greater<>> pq;
    D[2] = 0;
    pq.push({D[2], 2});

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

    dp[2] = 1;
    cout << DFS(1);
}
