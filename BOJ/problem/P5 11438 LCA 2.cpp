// URL: https://www.acmicpc.net/problem/4179
// Algo: LCA 기본 (DP응용 O(log depth))

// Start:	240830 07 20
// Read:	0 1
// Think:	0 8
// Code:	0 16
// Total:	0 25

// 이론상 p[i][k]보다 p[k][i]가 더 캐시 히트율이 높아야하는데 84ms -> 120ms로 더 느리다. 흠...
// n이랑 k가 더 커지면 효과가 있나?

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) x.begin(), x.end()
#define pb push_back

int n, kNum;
vector<int> adj[100'001];

int p[17][100'001]; // p[k][i]: i 노드의 2^k번째 조상
int depth[100'001];

void DFS(int cur)
{
    for (const int nxt : adj[cur])
    {
        if (depth[nxt] != -1) continue;
        p[0][nxt] = cur;
        depth[nxt] = depth[cur] + 1;
        DFS(nxt);
    }
}

int LCA(int a, int b)
{
    if (depth[a] < depth[b]) swap(a, b);

    const int diff = depth[a] - depth[b];
    for (int k = kNum - 1; k >= 0; --k)
    {
        if (diff & 1 << k) a = p[k][a];
    }

    if (a == b) return a;

    for (int k = kNum - 1; k >= 0; --k)
    {
        if (p[k][a] != p[k][b])
        {
            a = p[k][a];
            b = p[k][b];
        }
    }
    return p[0][a];
}

int main()
{
    fastio;
    memset(depth, -1, sizeof(depth));

    cin >> n;
    kNum = log2(n) + 1;
    for (int i = 0; i < n - 1; ++i)
    {
        int a, b;
        cin >> a >> b;
        adj[a].pb(b);
        adj[b].pb(a);
    }

    depth[1] = 0;
    DFS(1);

    for (int k = 1; k < kNum; ++k)
    {
        for (int i = 1; i <= n; ++i)
        {
            p[k][i] = p[k-1][p[k-1][i]];
        }
    }

    int T;
    cin >> T;
    while (T--)
    {
        int a, b;
        cin >> a >> b;
        cout << LCA(a, b) << '\n';
    }
}
