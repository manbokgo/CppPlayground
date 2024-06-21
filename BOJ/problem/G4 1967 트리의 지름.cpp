// URL: https://www.acmicpc.net/problem/1967
// Algo: DFS, 트리

// Start:	240622 07 13
// Read:	0 1
// Think:	0 0
// Code:	0 1
// Total:   0 2

// G2 1167 트리의 지름 문제 복붙날먹. 똑같은거 구하는 문제인데 이건 왜 G4임?

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) x.begin(), x.end()
#define pb push_back

using ll = long long;
using pii = pair<int, int>;

int n;
vector<pii> adj[10'001];
bool visited[10'001];
int maxDist = 0;
int maxNode = -1;

void DFS(int node, int dist)
{
    visited[node] = true;

    if (dist > maxDist)
    {
        maxDist = dist;
        maxNode = node;
    }

    for (auto [cNode, cDist] : adj[node])
    {
        if (visited[cNode]) continue;
        DFS(cNode, dist + cDist);
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 0; i < n - 1; ++i)
    {
        int a, b, c;
        cin >> a >> b >> c;
        adj[a].pb({b, c});
        adj[b].pb({a, c});
    }

    DFS(1, 0);

    maxDist = 0;
    memset(visited, false, sizeof(visited));
    DFS(maxNode, 0);

    cout << maxDist;
}
