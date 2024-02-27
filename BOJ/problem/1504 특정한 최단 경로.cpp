// URL: https://www.acmicpc.net/problem/1504
// Algo: 다익스트라

// Start:	240227 22 04
// Read:	0 0
// Think:	0 1
// Code:	0 22
// Total:	0 23

// 다익스트라 1, V1, V2 시작으로 총 3번 돌려서
// 1toV1, 1toV2, V1toV2, V1toN, V2toN 찾아서 짧은 루트 찾기

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

vector<pii> adj[805]; // {비용, 도착정점}
int         d[805];

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, e;
    cin >> n >> e;

    while (e--)
    {
        int a, b, c;
        cin >> a >> b >> c;
        adj[a].pb({c, b});
        adj[b].pb({c, a});
    }

    int v1, v2;
    cin >> v1 >> v2;

    // 실수: v1 먼저 갔다 v2가는 경로, v2 먼저 갔다 v1가는 경로
    int answer1 = 0;
    int answer2 = 0;

    // {비용, 정점}
    priority_queue<pii, vector<pii>, greater<>> pq;


    fill(d, d + n + 1, INF);
    pq.push({0, 1});
    d[1] = 0;

    while (!pq.empty())
    {
        auto [dist, node] = pq.top();
        pq.pop();

        if (d[node] != dist) continue;
        for (auto [nDist, nNode] : adj[node])
        {
            if (d[nNode] <= d[node] + nDist) continue;
            d[nNode] = d[node] + nDist;
            pq.push({d[nNode], nNode});
        }
    }

    answer1 += d[v1]; // [1] 1 -> v1
    answer2 += d[v2]; // [2] 1 -> v2

    fill(d, d + n + 1, INF);
    pq.push({0, v1});
    d[v1] = 0;

    while (!pq.empty())
    {
        auto [dist, node] = pq.top();
        pq.pop();

        if (d[node] != dist) continue;
        for (auto [nDist, nNode] : adj[node])
        {
            if (d[nNode] <= d[node] + nDist) continue;
            d[nNode] = d[node] + nDist;
            pq.push({d[nNode], nNode});
        }
    }

    // 실수: v1<->v2 경로 없으면 무조건 뻑남
    if (d[v2] == INF)
    {
        cout << -1;
        return 0;
    }

    answer1 += d[v2]; // [1] v1 -> v2
    answer2 += d[v2]; // [2] v2 -> v1 위와 비용 동일
    answer2 += d[n];  // [2] v1 -> n 최종

    fill(d, d + n + 1, INF);
    pq.push({0, v2});
    d[v2] = 0;

    while (!pq.empty())
    {
        auto [dist, node] = pq.top();
        pq.pop();

        if (d[node] != dist) continue;
        for (auto [nDist, nNode] : adj[node])
        {
            if (d[nNode] <= d[node] + nDist) continue;
            d[nNode] = d[node] + nDist;
            pq.push({d[nNode], nNode});
        }
    }

    answer1 += d[n]; // [1] v2 -> n 최종

    int finalAns = min(answer1, answer2);

    if (finalAns >= INF) cout << -1;
    else cout << finalAns;
}
