#include <bits/stdc++.h>

using namespace std;
const int MAX_V = 401;
const int INF = 100000000;

struct Edge
{
    int to, c, f;
    Edge *dual;
    Edge(int to, int c) : to(to), c(c), f(0), dual(nullptr) {}
    int spare()
    {
        return c - f;
    }
    void addFlow(int flow)
    {
        f += flow;
        dual->f -= flow;
    }
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, p;
    vector<Edge *> adj[MAX_V];
    cin >> n >> p;

    int S = 1;
    int E = 2;
    Edge *e1;
    Edge *e2;

    while (p--)
    {
        int u, v;
        cin >> u >> v;
        e1 = new Edge(v, 1);
        e2 = new Edge(u, 0);
        e1->dual = e2;
        e2->dual = e1;
        adj[u].push_back(e1);
        adj[v].push_back(e2);
    }

    int total = 0;
    while (true)
    {
        int prev[MAX_V];
        Edge *path[MAX_V] = {};
        fill(prev, prev + MAX_V, -1);
        queue<int> Q;
        Q.push(S);

        while (!Q.empty() && prev[E] == -1)
        {
            int cur = Q.front();
            Q.pop();
            for (Edge *e : adj[cur])
            {
                int next = e->to;
                if (e->spare() > 0 && prev[next] == -1)
                {
                    Q.push(next);
                    prev[next] = cur;
                    path[next] = e;
                    if (next == E)
                        break;
                }
            }
        }
        if (prev[E] == -1)
            break;

        int flow = INF;
        for (int i = E; i != S; i = prev[i])
        {
            flow = min(flow, path[i]->spare());
        }
        for (int i = E; i != S; i = prev[i])
        {
            path[i]->addFlow(flow);
        }
        total += flow;
    }

    cout << total;
}