#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define findvec(x, value) find(all(x), value) != x.end()

using namespace std;
const int MAX_V = 301;
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

    int tc;
    cin >> tc;
    while (tc--)
    {
        int n, m;
        vector<Edge *> adj[MAX_V];
        cin >> n >> m;

        int S = 1;
        int E = n;
        Edge *e1;
        Edge *e2;

        while (m--)
        {
            int u, v, w;
            cin >> u >> v >> w;
            e1 = new Edge(v, w);
            e2 = new Edge(u, 0);
            e1->dual = e2;
            e2->dual = e1;
            adj[u].push_back(e1);
            adj[v].push_back(e2);
        }

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
        }

        int crucial = 0;
        for (int i = 1; i <= n; ++i)
        {
            for (Edge *e : adj[i])
            {
                if (e->c > 0 && e->spare() == 0)
                {
                    int flank = e->to;
                    while (true)
                    {
                        int prev[MAX_V];
                        Edge *path[MAX_V] = {};
                        fill(prev, prev + MAX_V, -1);
                        queue<int> Q;
                        Q.push(i);

                        while (!Q.empty() && prev[flank] == -1)
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
                                    if (next == flank)
                                        break;
                                }
                            }
                        }
                        if (prev[flank] == -1)
                            ++crucial;
                        break;
                    }
                }
            }
        }
        cout << crucial << '\n';
    }
}