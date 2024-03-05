// URL: https://www.acmicpc.net/problem/10282
// Algo: 다익스트라 기본

// Start:	240218 22 42
// Read:	0 0
// Think:	0 0
// Code:	0 10
// Total:	0 10

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

constexpr ll  MOD = 1000000007;
constexpr int INF = 0x3f3f3f3f;
constexpr ll  LLINF = 1e18;

vector<pii> adj[10005]; // [비용, 도착정점]
int         d[10005];   // 최단거리

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t, n, m, c;
    cin >> t;

    while (t--)
    {
        for (auto& ad : adj)
            ad.clear();

        fill_n(d, 10005, INF);

        cin >> n >> m >> c;

        while (m--)
        {
            int a, b, s;
            cin >> a >> b >> s;
            adj[b].pb({s, a});
        }

        priority_queue<pii, vector<pii>, greater<>> pq;

        d[c] = 0;
        pq.push({0, c});

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

        int affected = 0;
        int maxDist = 0;
        for (int i = 1; i <= n; ++i)
        {
            int finalD = d[i];
            if (finalD < INF)
            {
                ++affected;
                maxDist = max(maxDist, finalD);
            }
        }

        cout << affected << " " << maxDist << "\n";
    }
}
