#include <bits/stdc++.h>

using namespace std;
const int MAX_V = 800;
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

    for (int v = 0; v < n; ++v)
    {
        int inputV = v * 2;
        int outputV = inputV + 1;

        e1 = new Edge(outputV, 1);
        e2 = new Edge(inputV, 0);
        e1->dual = e2;
        e2->dual = e1;
        adj[inputV].push_back(e1);
        adj[outputV].push_back(e2);
    }

    while (p--)
    {
        int u, v;
        cin >> u >> v;
        --u;
        --v;
        int inputU = u * 2;
        int outputU = inputU + 1;
        int inputV = v * 2;
        int outputV = inputV + 1;

        e1 = new Edge(inputV, 1);
        e2 = new Edge(outputU, 0);
        e1->dual = e2;
        e2->dual = e1;
        adj[outputU].push_back(e1);
        adj[inputV].push_back(e2);

        e1 = new Edge(inputU, 1);
        e2 = new Edge(outputV, 0);
        e1->dual = e2;
        e2->dual = e1;
        adj[outputV].push_back(e1);
        adj[inputU].push_back(e2);
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