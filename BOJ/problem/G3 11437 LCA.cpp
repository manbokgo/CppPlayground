// URL: https://www.acmicpc.net/problem/4179
// Algo: LCA 기본 (나이브 O(depth))

// Start:	240829 22 08
// Read:	0 1
// Think:	0 3
// Code:	0 10
// Total:	0 14

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) x.begin(), x.end()
#define pb push_back

int n;
vector<int> adj[50'001];

int p[50'001];
int depth[50'001];

void DFS(int cur)
{
    for (const int nxt : adj[cur])
    {
        if (depth[nxt] != -1) continue;
        p[nxt] = cur;
        depth[nxt] = depth[cur] + 1;
        DFS(nxt);
    }
}

int LCA(int a, int b)
{
    if (depth[a] < depth[b]) swap(a, b);
    while (depth[a] != depth[b]) a = p[a];
    while (a != b)
    {
        a = p[a];
        b = p[b];
    }
    return a;
}

int main()
{
    fastio;
    memset(depth, -1, sizeof(depth));
    memset(p, -1, sizeof(p));

    cin >> n;
    for (int i = 0; i < n - 1; ++i)
    {
        int a, b;
        cin >> a >> b;
        adj[a].pb(b);
        adj[b].pb(a);
    }

    depth[1] = 0;
    DFS(1);

    int T;
    cin >> T;
    while (T--)
    {
        int a, b;
        cin >> a >> b;
        cout << LCA(a, b) << '\n';
    }
}
