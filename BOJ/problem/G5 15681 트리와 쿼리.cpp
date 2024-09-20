// URL: https://www.acmicpc.net/problem/15681
// Algo: DFS, 트리

// Start:	240919 09 26
// Read:	0 1
// Think:	0 1
// Code:	0 4
// Total:	0 6

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) x.begin(), x.end()
#define pb push_back

int dp[100'001];
vector<int> adj[100'001];

int DFS(int cur, int parent)
{
    if (dp[cur] != -1) return dp[cur];

    dp[cur] = 1;
    for (const auto nxt : adj[cur])
    {
        if (nxt == parent) continue;
        dp[cur] += DFS(nxt, cur);
    }
    return dp[cur];
}

int main()
{
    fastio;
    memset(dp, -1, sizeof(dp));

    int n, r, q;
    cin >> n >> r >> q;
    for (int i = 0; i < n - 1; ++i)
    {
        int a, b;
        cin >> a >> b;
        adj[a].pb(b);
        adj[b].pb(a);
    }

    DFS(r, -1);
    while (q--)
    {
        int num;
        cin >> num;
        cout << dp[num] << '\n';
    }
}
