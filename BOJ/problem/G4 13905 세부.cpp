// URL: https://www.acmicpc.net/problem/13905
// Algo: MST 크루스칼 변형 or 다익스트라 변형

// Start:	240803 08 32
// Read:	0 3
// Think:	0 4
// Code:	0 30
// Total:	0 37
// 오모시로이

// 최소 스패닝 트리가 아니라 최대 스패닝 트리를 만들면 된다.
// 만드는 과정 중에 s와 e의 부모가 같아지면 서로가 연결되었다는 것을 의미하며,
// 비용 내림차순으로 순회하던만큼 그때까지의 최소값이 서로 간의 간선 중 최소값을 의미한다.
// 그런데 틀림... 뭔가 잘못 생각했나 싶어서 같이 떠올랐던 다익스트라 방법으로 시도해봄

// 공교롭게도 직전 P5 13308 주유소 문제에서 적용한 다익스트라 변형 최적화 방법이 가능했음
// 그런데 또 틀림...

// 결국 질문게시판 보니깐 '도착지에 도달하지 못하는 경우가 있음'이라는 말이 문제에서 빠졌다고 한다.
// 아니 빼빼로 선물해준다고 계획한 놈이 아예 길이 없는 섬으로 여친을 보내버렸다고??
// 문제 맥락만 안 이랬어도 의심할만한 경우였는데 어이가 없다

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) x.begin(), x.end()
#define pb push_back

constexpr int INF = 0x3f3f3f3f;
using pii = pair<int, int>;
using tiii = tuple<int, int, int>;

// MST 크루스칼 변형
int p[100'001];
tiii edge[300'000];
int answer = INF;

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
    fastio;
    memset(p, -1, sizeof(p));

    int n, m, s, e;
    cin >> n >> m >> s >> e;
    for (int i = 0; i < m; ++i)
    {
        auto& [c, a, b] = edge[i];
        cin >> a >> b >> c;
    }
    sort(edge, edge + m, greater<>());

    int cnt = 0;
    for (int i = 0; i < m; ++i)
    {
        auto [cost, a, b] = edge[i];
        if (!Union(a, b)) continue;

        answer = min(answer, cost);
        if (Find(s) == Find(e)) break;

        ++cnt;
        if (cnt == n - 1) break;
    }

    if (Find(s) == Find(e)) cout << answer;
    else cout << 0;
}



// 다익스트라 변형
/*
int D[100'001];
vector<pii> adj[100'001];

int main()
{
    fastio;
    memset(D, -1, sizeof(D));

    int n, m, s, e;
    cin >> n >> m >> s >> e;
    while (m--)
    {
        int a, b, c;
        cin >> a >> b >> c;
        adj[a].pb({c, b});
        adj[b].pb({c, a});
    }

    priority_queue<pii> pq; // 내림차순
    D[s] = INF;
    pq.push({D[s], s});

    while (!pq.empty())
    {
        const auto [dist, node] = pq.top();
        pq.pop();

        if (D[node] != dist) continue;
        for (const auto [nDist, nNode] : adj[node])
        {
            const int mn = min(dist, nDist);
            if (D[nNode] >= mn) continue;
            D[nNode] = mn;
            pq.push({D[nNode], nNode});
        }
    }

    if (D[e] == -1) cout << 0;
    else cout << D[e];
}
*/
