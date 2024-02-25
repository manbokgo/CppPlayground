// URL: https://www.acmicpc.net/problem/13418
// Algo: MST 크루스칼

// Start:	240225 17 41
// Read:	0 2
// Think:	0 1
// Code:	0 11
// Total:	

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
using tlll = tuple<ll, ll, ll>;

constexpr int INF = 0x3f3f3f3f;
// constexpr ll  LLINF = 1e18;
// constexpr ll  MOD = 1000000007;

// int dy[4] = {0, 1, 0, -1};
// int dx[4] = {1, 0, -1, 0}; // 동남서북
// bool OOB(int y, int x) { return y < 0 || y >= n || x < 0 || x >= m; }

// {비용, a, b}
tiii edge[500'000];
int  p[500'000];

int Find(int a)
{
    if (p[a] < 0) return a;
    return p[a] = Find(p[a]);
}

bool Union(int a, int b)
{
    int ap = Find(a);
    int bp = Find(b);
    if (ap == bp) return false;

    if (-p[ap] < -p[bp]) swap(ap, bp);
    p[ap] += p[bp];
    p[bp] = ap;
    return true;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    // 0번 노드와, 0번-1번 간선이 무조건 더 존재
    ++n;
    ++m;

    for (int i = 0; i < m; ++i)
    {
        int a, b, c;
        cin >> a >> b >> c;

        // 0이 오르막길
        if (c == 0) c = 1;
        else c = 0;

        edge[i] = {c, a, b};
    }

    sort(edge, edge + m);

    
    memset(p, -1, sizeof(p));
    int count = 0;
    int minHeight = 0;
    for (int i = 0; i < m; ++i)
    {
        auto [cost, a, b] = edge[i];
        if (!Union(a, b)) continue;
        ++count;
        minHeight += cost;
        if (count == n - 1) break;
    }

    memset(p, -1, sizeof(p));
    count = 0;
    int maxHeight = 0;
    for (int i = m - 1; i > 0; --i)
    {
        auto [cost, a, b] = edge[i];
        if (!Union(a, b)) continue;
        ++count;
        maxHeight += cost;
        if (count == n - 1) break;
    }

    cout << maxHeight * maxHeight - minHeight * minHeight;
}
