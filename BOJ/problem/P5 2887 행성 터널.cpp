// URL: https://www.acmicpc.net/problem/2887
// Algo: MST 크루스칼

// Start:	240225 18 18
// Read:	0 0
// Think:	0 13
// Code:	0 23  Find 함수 오타에 해맴.
// Total:	0 36

// 행성간 이동 비용이 정말 3차원 거리였다면 O(V^2)으로 한 행성에서 모든 행성까지의 간선을 만들었어야겠지만
// (더 효율적으로 하는 방법은 충돌 알고리즘 Broad Phase에서 쓰는
// Sweep And Prune 같은 최적화 기법을 응용하면 될 거 같기도 한데 최악의 경우 고려하면 그게 그거일듯)
//
// 문제에서의 행성 이동 비용은 min(|xA-xB|, |yA-yB|, |zA-zB|) 라는 기묘한 공식이어서
// 각 x/y/z축 상에서 가장 가까운 양 옆 행성까지의 간선들만 만들어내고 크루스칼 돌리면 됨

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

int p[100'001];

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

struct Coord
{
    int x;
    int y;
    int z;
    int idx;
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    memset(p, -1, sizeof(p));

    int n;
    cin >> n;

    vector<Coord> nodes(n);

    // {비용, a, b}
    vector<tiii> edges;
    edges.reserve(3 * n); // 실제 최대 수는 3(n-1)

    for (int i = 0; i < n; ++i)
    {
        int x, y, z;
        cin >> x >> y >> z;
        nodes[i] = {x, y, z, i};
    }

    // x로 정렬. n-1개 간선 추가
    sort(all(nodes), [](Coord a, Coord b) { return a.x < b.x; });
    for (int i = 1; i < n; ++i)
    {
        edges.pb({abs(nodes[i].x - nodes[i - 1].x), nodes[i - 1].idx, nodes[i].idx});
    }

    // y로 정렬. n-1개 간선 추가
    sort(all(nodes), [](Coord a, Coord b) { return a.y < b.y; });
    for (int i = 1; i < n; ++i)
    {
        edges.pb({abs(nodes[i].y - nodes[i - 1].y), nodes[i - 1].idx, nodes[i].idx});
    }

    // z로 정렬. n-1개 간선 추가
    sort(all(nodes), [](Coord a, Coord b) { return a.z < b.z; });
    for (int i = 1; i < n; ++i)
    {
        edges.pb({abs(nodes[i].z - nodes[i - 1].z), nodes[i - 1].idx, nodes[i].idx});
    }

    sort(all(edges));

    int count = 0;
    int answer = 0;
    for (auto [cost, a, b] : edges)
    {
        if (!Union(a, b)) continue;
        ++count;
        answer += cost;
        if (count == n - 1) break;
    }

    cout << answer;
}
