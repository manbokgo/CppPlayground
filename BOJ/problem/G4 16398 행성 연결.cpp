// URL: https://www.acmicpc.net/problem/16398
// Algo: MST 크루스칼 or 프림 나이브

// Start:	241017 12 34
// Read:	0 1
// Think:	0 1
// Code:	0 4
// Total:	0 6

// 인접 행렬로 데이터가 주어지는데, 크루스칼로 풀려면 인접 리스트로 변환해야 했다.

// 모든 노드 간에 간선이 존재하는 E가 매우 큰 상황이므로 O(ElogE)인 크루스칼보다
// 인접 행렬을 그대로 쓰도록 수정한 O(ElogV)인 프림이 더 효율적이라 생각해서 해보니
// 113MB 148ms -> 153MB 132ms 로 큰 차이는 없었다.

// 다익스트라 나이브 버전과 같이, 프림 나이브 O(V^2+E)를 짜서 돌려보니 60MB 128ms
// 오랜만에 복습한 셈 치자

// 인접 리스트 -> 인접 행렬 변환할 때 참고
// for (int i = 0; i < n; ++i)
// {
//     if (chk[i]) continue;
//     pq.push({adj[0][i], 0, i});
// }

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) x.begin(), x.end()
#define pb push_back

using pii = pair<int, int>;
using tiii = tuple<int, int, int>;
using ll = long long;

constexpr int INF = 0x3f3f3f3f;

int n;

int p[1'000];

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

void SolveKruskal()
{
    memset(p, -1, sizeof(p));
    vector<tiii> edges;
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            int num;
            cin >> num;
            if (j <= i) continue;
            edges.pb({num, i, j});
        }
    }
    sort(all(edges));

    int count = 0;
    ll answer = 0;
    for (const auto& [cost, a, b] : edges)
    {
        if (!Union(a, b)) continue;
        ++count;
        answer += cost;

        if (count == n - 1) break;
    }

    cout << answer;
}

void SolvePrim()
{
    vector<vector<int>> adj(n, vector<int>(n));
    vector<bool> chk(n);
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            cin >> adj[i][j];
        }
    }

    int count = 0;
    ll answer = 0;

    priority_queue<tiii, vector<tiii>, greater<>> pq;

    chk[0] = true;
    for (int i = 0; i < n; ++i)
    {
        if (chk[i]) continue;
        pq.push({adj[0][i], 0, i});
    }

    while (count < n - 1)
    {
        const auto [cost, a, b] = pq.top();
        pq.pop();

        if (chk[b]) continue;

        ++count;
        answer += cost;
        chk[b] = true;
        for (int i = 0; i < n; ++i)
        {
            if (chk[i]) continue;
            pq.push({adj[b][i], b, i});
        }
    }

    cout << answer;
}

void SolvePrimNaive()
{
    vector<vector<int>> adj(n, vector<int>(n));
    vector<bool> chk(n);
    vector<int> dist(n, INF);

    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            cin >> adj[i][j];
        }
    }

    ll answer = 0;

    dist[0] = 0;
    for (int cnt = 0; cnt < n; ++cnt)
    {
        int idx = -1;
        for (int i = 0; i < n; ++i)
        {
            if (chk[i]) continue;
            if (idx == -1 || dist[idx] > dist[i]) idx = i;
        }

        chk[idx] = true;
        answer += dist[idx];
        for (int i = 0; i < n; ++i)
        {
            dist[i] = min(dist[i], adj[idx][i]);
        }
    }

    cout << answer;
}

int main()
{
    fastio;
    cin >> n;

    SolveKruskal();
    // SolvePrim();
    // SolvePrimNaive();
}
