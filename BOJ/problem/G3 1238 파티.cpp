// URL: https://www.acmicpc.net/problem/1238
// Algo: 다익스트라 (단방향 All to One)

// Start:	
// Read:	0 2
// Think:	0 3
// Code:	0 7
// Total:	0 12

// 다익스트라는 시작 노드에서 모든 노드까지의 최단거리를 구하는 알고리즘이다. One to All

// 양방향 그래프라면 이는 동시에 모든 노드에서 시작 노드까지의 최단거리를 의미하기도 한다.
// 단방향 그래프에서는 '역간선'으로 다익스트라를 돌려서
// 모든 노드에서 시작 노드까지 도달하는 최단거리를 구할 수 있다. All to One

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) x.begin(), x.end()
#define pb push_back

using pii = pair<int, int>;

vector<pii> adj[1'001];
vector<pii> adjR[1'001];
int d[1'001];
int dR[1'001];

int main()
{
    fastio;
    memset(d, 0x3f, sizeof(d));
    memset(dR, 0x3f, sizeof(dR));

    int n, m, x;
    cin >> n >> m >> x;

    while (m--)
    {
        int a, b, c;
        cin >> a >> b >> c;
        adj[a].pb({c, b});
        adjR[b].pb({c, a});
    }

    priority_queue<pii, vector<pii>, greater<>> pq;

    d[x] = 0;
    pq.push({d[x], x});

    while (!pq.empty())
    {
        auto [dist, node] = pq.top();
        pq.pop();

        if (dist != d[node]) continue;
        for (auto [nxtDist, nxtNode] : adj[node])
        {
            if (d[nxtNode] <= dist + nxtDist) continue;
            d[nxtNode] = dist + nxtDist;
            pq.push({d[nxtNode], nxtNode});
        }
    }

    dR[x] = 0;
    pq.push({dR[x], x});

    while (!pq.empty())
    {
        auto [dist, node] = pq.top();
        pq.pop();

        if (dist != dR[node]) continue;
        for (auto [nxtDist, nxtNode] : adjR[node])
        {
            if (dR[nxtNode] <= dist + nxtDist) continue;
            dR[nxtNode] = dist + nxtDist;
            pq.push({dR[nxtNode], nxtNode});
        }
    }

    int answer = -1;
    for (int i = 1; i <= n; ++i)
        answer = max(answer, d[i] + dR[i]);

    cout << answer;
}
