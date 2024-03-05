// URL: https://www.acmicpc.net/problem/14938
// Algo: 플로이드 or 다익스트라 V번

// Start:	240305 21 23
// Read:	0 0
// Think:	0 5
// Code:	0 17
// Total:	0 22

#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define Y first
#define X second
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

// 플로이드 풀이
int item[101]; // 아이템 수
int dist[101][101];

int n, m, r;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    fill(&dist[0][0], &dist[101][101], INF);

    cin >> n >> m >> r;

    for (int i = 1; i <= n; ++i) // 실수: i=0 부터 잘못 시작함
    {
        cin >> item[i];
    }

    while (r--)
    {
        int a, b, cost;
        cin >> a >> b >> cost;

        dist[a][b] = cost;
        dist[b][a] = cost;
    }


    for (int k = 1; k <= n; ++k)
    {
        dist[k][k] = 0;
        for (int i = 1; i <= n; ++i)
        {
            for (int j = 1; j <= n; ++j)
            {
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }

    int answer = 0;
    for (int i = 1; i <= n; ++i)
    {
        int sum = 0;
        for (int j = 1; j <= n; ++j)
        {
            if (dist[i][j] > m) continue;
            sum += item[j];
        }

        answer = max(answer, sum);
    }

    cout << answer;
}


// 다익스트라 V번 풀이
/*
int         item[101]; // 아이템 수
vector<pii> adj[101]; // {비용, 도착정점}
int         d[101];

int n, m, r;

int dijkstra(int startNode)
{
    fill_n(d, 101, INF);
    priority_queue<pii, vector<pii>, greater<>> pq;

    d[startNode] = 0;
    pq.push({0, startNode});

    while (!pq.empty())
    {
        auto [dist, node] = pq.top();
        pq.pop();

        if (d[node] != dist) continue;
        for (auto [nxtDist, nxtNode] : adj[node])
        {
            if (d[nxtNode] <= d[node] + nxtDist) continue;
            d[nxtNode] = d[node] + nxtDist;
            pq.push({d[nxtNode], nxtNode});
        }
    }

    int sum = 0;
    for (int i = 1; i <= n; ++i)
    {
        if (d[i] > m) continue;
        sum += item[i];
    }

    return sum;
}


int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m >> r;
    for (int i = 1; i <= n; ++i)
    {
        cin >> item[i];
    }

    while (r--)
    {
        int a, b, cost;
        cin >> a >> b >> cost;

        adj[a].pb({cost, b});
        adj[b].pb({cost, a});
    }


    int answer = 0;
    for (int i = 1; i <= n; ++i)
    {
        answer = max(answer, dijkstra(i));
    }

    cout << answer;
}
*/
