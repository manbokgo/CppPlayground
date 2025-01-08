// URL: https://www.acmicpc.net/problem/11725
// Algo: 트리, DFS

// Start:	250108 19 48
// Read:	0 1
// Think:	0 2
// Code:	0 3
// Total:	0 6

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) x.begin(), x.end()
#define pb push_back

bool visited[100'001];
vector<int> adj[100'001];
int p[100'001];

void DFS(int cur)
{
    visited[cur] = true;
    for (const int nxt : adj[cur])
    {
        if (visited[nxt]) continue;
        p[nxt] = cur;
        DFS(nxt);
    }
}

int main()
{
    fastio;

    int n;
    cin >> n;

    for (int i = 0; i < n - 1; ++i)
    {
        int a, b;
        cin >> a >> b;
        adj[a].pb(b);
        adj[b].pb(a);
    }

    DFS(1);
    for (int i = 2; i <= n; ++i)
        cout << p[i] << '\n';
}
