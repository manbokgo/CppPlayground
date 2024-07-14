// URL: https://www.acmicpc.net/problem/16118
// Algo: 다익스트라 변형

// Start:	240714 18 15
// Read:	0 2
// Think:	0 5
// Code:	0 20
// Total:	0 27

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) x.begin(), x.end()
#define pb push_back

constexpr int INF = 0x3f3f3f3f;

using pii = pair<int, int>;
using tiii = tuple<int, int, int>;

int n, m;
int DFox[4001];
int DWolf[4001][2];
vector<pii> adj[4001];

int main()
{
    fastio;
    memset(DFox, INF, sizeof(DFox));
    memset(DWolf, INF, sizeof(DWolf));

    cin >> n >> m;
    while (m--)
    {
        int a, b, c;
        cin >> a >> b >> c;
        c *= 2; // 소숫점 싫어
        adj[a].pb({c, b});
        adj[b].pb({c, a});
    }

    {
        priority_queue<pii, vector<pii>, greater<>> pq;

        DFox[1] = 0;
        pq.push({DFox[1], 1});

        while (!pq.empty())
        {
            const auto [dist, node] = pq.top();
            pq.pop();

            if (dist != DFox[node]) continue;
            for (const auto [nDist, nNode] : adj[node])
            {
                if (DFox[nNode] <= dist + nDist) continue;
                DFox[nNode] = dist + nDist;
                pq.push({DFox[nNode], nNode});
            }
        }
    }

    {
        priority_queue<tiii, vector<tiii>, greater<>> pq; // dist, node, tired

        DWolf[1][0] = 0;
        // 실수: DWolf[1][1] = 0; 다른 정점 돌고 tired 상태로 1정점 돌아왔을 때 잘못된 값 나온다
        pq.push({DWolf[1][0], 1, 0});

        while (!pq.empty())
        {
            const auto [dist, node, tired] = pq.top();
            pq.pop();

            if (dist != DWolf[node][tired]) continue;
            for (auto [nDist, nNode] : adj[node])
            {
                if (tired) nDist *= 2;
                else nDist /= 2;

                if (DWolf[nNode][!tired] <= dist + nDist) continue;
                DWolf[nNode][!tired] = dist + nDist;
                pq.push({DWolf[nNode][!tired], nNode, !tired});
            }
        }
    }

    int answer = 0;
    for (int i = 1; i <= n; ++i)
    {
        if (DFox[i] < min(DWolf[i][0], DWolf[i][1])) ++answer;
    }
    cout << answer;
}
