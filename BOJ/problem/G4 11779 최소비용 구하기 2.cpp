// URL: https://www.acmicpc.net/problem/11779
// Algo: 다익스트라 + 경로 복원

// Start:	240617 12 53
// Read:	0 1
// Think:	0 0
// Code:	0 6
// Total:	0 7

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) x.begin(), x.end()
#define pb push_back

constexpr int INF = 0x3f3f3f3f;
using pii = pair<int, int>;

int n, m;
int st, en;
vector<pii> adj[1'001];
int d[1'001];
int pre[1'001];

int main()
{
    fastio;
    memset(d, 0x3f, sizeof(d));
    memset(pre, -1, sizeof(pre));

    cin >> n >> m;
    while (m--)
    {
        int a,b,c;
        cin >> a >> b >> c;
        adj[a].pb({c, b});
    }
    cin >> st >> en;

    priority_queue<pii, vector<pii>, greater<>> pq;
    d[st] = 0;
    pq.push({d[st], st});

    while (!pq.empty())
    {
        const auto [dist, node] = pq.top();
        pq.pop();

        if (dist != d[node]) continue;
        for (const auto [nDist, nNode] : adj[node])
        {
            if (d[nNode] <= dist + nDist) continue;
            d[nNode] = dist + nDist;
            pq.push({d[nNode], nNode});
            pre[nNode] = node;
        }
    }

    vector<int> answer;
    int cur = en;
    while (cur != st)
    {
        answer.pb(cur);
        cur = pre[cur];
    }
    answer.pb(cur);
    reverse(all(answer));

    cout << d[en] << '\n';
    cout << answer.size() << '\n';
    for (const auto node : answer) cout << node << ' ';
}
