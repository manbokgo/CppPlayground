// 다익스트라
#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> pii;
const int INF = 10000000000;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int vertex, e, s;
    cin >> vertex >> e >> s;
    --s;
    vector<pii> adj[vertex];

    while (e--)
    {
        int u, v, w;
        cin >> u >> v >> w;
        --u;
        --v;
        adj[u].push_back(pii(v, w));
    }

    int dist[vertex];
    fill(dist, dist + vertex, INF);
    bool visit[vertex] = {};
    priority_queue<pii, vector<pii>, greater<pii>> PQ;

    dist[s] = 0;
    PQ.push(pii(0, s));

    while (!PQ.empty())
    {
        int cur;
        do
        {
            cur = PQ.top().second;
            PQ.pop();
        } while (!PQ.empty() && visit[cur]);

        if (visit[cur])
            break;

        visit[cur] = true;
        for (auto &&i : adj[cur])
        {
            int target = i.first;
            int cost = i.second;

            if (dist[cur] + cost < dist[target])
            {
                dist[target] = dist[cur] + cost;
                PQ.push(pii(dist[target], target));
            }
        }
    }

    for (int i = 0; i < vertex; i++)
    {
        if (dist[i] != INF)
            cout << dist[i];
        else
            cout << "INF";
        cout << "\n";
    }
}