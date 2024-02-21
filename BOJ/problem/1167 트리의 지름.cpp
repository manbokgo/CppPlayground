// URL: https://www.acmicpc.net/problem/1167
// Algo: DFS, 트리

// Start:	240222 00 46
// Read:	0 0
// Think:	0 1
// Code:	0 13
// Total:	0 14

#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define X first
#define Y second
#define all(x) x.begin(), x.end()
#define sortVec(x) sort(all(x))
#define compress(x) x.erase(unique(all(x)), x.end())
#define existInVec(x, value) find(all(x), value) != x.end()

using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using tiii = tuple<int, int, int>;

constexpr ll  MOD = 1000000007;
constexpr int INF = 0x3f3f3f3f;
constexpr ll  LLINF = 1e18;

vector<pii> adj[100'005];
bool        visited[100'005];

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

    int n;
    cin >> n;
    for (int i = 0; i < n; ++i)
    {
        int st, en, dist;
        cin >> st;

        while (true)
        {
            cin >> en;
            if (en == -1) break;
            cin >> dist;
            adj[st].pb({en, dist});
        }
    }

    // 임의의 한 점에서 가장 멀리있는거 찾고
    DFS(1, 0);

    maxDist = 0;
    memset(visited, false, sizeof(visited));

    // 거기에서 가장 멀리있는거 찾으면, 그 사이 거리가
    // 임의의 두 점 사이의 거리 중 가장 긴 것 (트리의 지름)
    DFS(maxNode, 0);

    cout << maxDist;
}
