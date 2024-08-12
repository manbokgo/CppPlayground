// URL: https://www.acmicpc.net/problem/2610
// Algo: 플로이드, 분리 집합

// Start:	240813 08 00
// Read:	0 2
// Think:	0 3
// Code:	0 11
// Total:	0 16

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) x.begin(), x.end()
#define pb push_back

constexpr int INF = 0x3f3f3f3f;

int dist[101][101];
int p[101];
int mxDist[101];

int Find(int a)
{
    if (p[a] < 0) return a;
    p[a] = Find(p[a]);
    return p[a];
}

// 변형
bool Union(int a, int b)
{
    int ap = Find(a);
    int bp = Find(b);

    if (ap == bp) return false;
    // if (-p[ap] < -p[bp]) swap(ap, bp);
    if (mxDist[ap] > mxDist[bp]) swap(ap, bp);

    p[ap] += p[bp];
    p[bp] = ap;
    return true;
}


int main()
{
    fastio;
    memset(dist, INF, sizeof(dist));
    memset(p, -1, sizeof(p));

    int n, k;
    cin >> n >> k;

    for (int i = 1; i <= n; ++i)
        dist[i][i] = 0;

    while (k--)
    {
        int a, b;
        cin >> a >> b;
        dist[a][b] = 1;
        dist[b][a] = 1;
    }

    for (int k = 1; k <= n; ++k)
        for (int s = 1; s <= n; ++s)
            for (int e = 1; e <= n; ++e)
                dist[s][e] = min(dist[s][e], dist[s][k] + dist[k][e]);

    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= n; ++j)
        {
            if (dist[i][j] == INF) continue;
            mxDist[i] = max(mxDist[i], dist[i][j]);
        }
    }

    for (int i = 1; i <= n; ++i)
    {
        for (int j = i; j <= n; ++j)
        {
            if (dist[i][j] == INF) continue;
            Union(i, j);
        }
    }

    int cnt = 0;
    vector<int> answer;
    for (int i = 1; i <= n; ++i)
    {
        if (p[i] < 0) 
        {
            ++cnt;
            answer.pb(i);
        }
    }

    cout << cnt << '\n';
    for (const int num : answer) cout << num << '\n';
}
