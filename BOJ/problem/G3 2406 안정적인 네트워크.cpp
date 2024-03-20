// URL: https://www.acmicpc.net/problem/2406
// Algo: MST 크루스칼

// Start:	240313 19 02
// Read:	0 1
// Think:	0 7
// Code:	0 20
// Total:	0 28

#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define Y first
#define X second
#define all(x) x.begin(), x.end()
#define SortVec(x) sort(all(x))
#define CompressVec(x) x.erase(unique(all(x)), x.end())
#define ExistInVec(x, value) find(all(x), value) != x.end()

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

int p[1001];

int Find(int n)
{
    if (p[n] < 0) return n;
    return p[n] = Find(p[n]);
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

    memset(p, -1, sizeof(p));

    int n, m;
    cin >> n >> m;

    int validEdge = 0; // 실수: 이미 존재하는 간선이 2-3 3-4 2-4 같은 순환 간선이라면, 유효한 간선은 2-3 3-4 2개 뿐
    for (int i = 0; i < m; ++i)
    {
        int a, b;
        cin >> a >> b;
        validEdge += Union(a, b);
    }

    if (validEdge == n - 2)
    {
        cout << "0 0";
        return 0;
    }

    vector<tiii> edges; // {비용, a, b}
    edges.reserve(n * n / 2);
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= n; ++j)
        {
            int cost;
            cin >> cost;

            if (i >= 2 && j > i)
                edges.pb({cost, i, j});
        }
    }

    SortVec(edges);

    int count = 0;
    int ansCost = 0;
    vector<pii> ansVec;
    ansVec.reserve(n);

    for (auto [cost, a, b] : edges)
    {
        if (!Union(a, b)) continue;
        ++count;
        ansCost += cost;
        ansVec.pb({a, b});

        if (count == n - 2 - validEdge) break;
    }

    cout << ansCost << " " << count;
    if (count > 0)
    {
        cout << "\n";
        for (auto [a, b] : ansVec)
        {
            cout << a << " " << b << "\n";
        }
    }
}
