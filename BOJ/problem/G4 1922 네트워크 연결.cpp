// URL: https://www.acmicpc.net/problem/1922
// Algo: MST 크루스칼 기본, 프림 기본

// Start:	240209 00 32
// Read:	0 0
// Think:	0 0
// Code:	0 24
// Total:	0 24

#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define X first
#define Y second
#define all(x) x.begin(), x.end()
#define sortvec(x) sort(all(x))
#define compress(x) x.erase(unique(all(x)), x.end())
#define findvec(x, value) find(all(x), value) != x.end()

using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;

constexpr ll  MOD = 1000000007;
constexpr int INF = 0x3f3f3f3f;
constexpr ll  LLINF = 1e18;


int N, M;

// 크루스칼
// {비용, 노드1, 노드2}
tuple<int, int, int> edge[100'001];
int                  p[1'001];

// 프림
// {비용, 도착노드}
vector<pii> adj[100'001];
bool        chk[1'001];


int Find(int a)
{
    if (p[a] < 0) return a;
    p[a] = Find(p[a]);
    return p[a];
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

void SolveKruskal()
{
    for (int i = 0; i < M; ++i)
    {
        int a, b, c;
        cin >> a >> b >> c;

        edge[i] = {c, a, b};
    }


    sort(edge, edge + M);

    int count = 0;
    int answer = 0;

    for (int i = 0; i < M; ++i)
    {
        auto [cost, a, b] = edge[i];
        if (!Union(a, b)) continue;
        ++count;
        answer += cost;

        if (count == N - 1) break; // 실수: V-1이니깐 N-1임. M이 아니라.
    }

    cout << answer;
}

void SolvePrim()
{
    for (int i = 0; i < M; ++i)
    {
        int a, b, c;
        cin >> a >> b >> c;

        adj[a].pb({c, b});
        adj[b].pb({c, a});
    }

    int count = 0;
    int answer = 0;

    priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<>> pq;

    chk[1] = true;
    for (auto [cost, node] : adj[1])
    {
        pq.push({cost, 1, node});
    }

    while (count < N - 1)
    {
        auto [cost, a, b] = pq.top();
        pq.pop();

        if (chk[b]) continue;
        ++count;
        answer += cost;
        chk[b] = true;

        for (auto [cost, node] : adj[b])
        {
            if (!chk[node]) pq.push({cost, b, node});
        }
    }

    cout << answer;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    memset(p, -1, sizeof(p));

    cin >> N >> M;

    SolveKruskal();
    // SolvePrim();
}
