#include <bits/stdc++.h>

using namespace std;
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

    int t;
    cin >> t;
    while (t--)
    {
        int n, m;
        cin >> n >> m;
        int MAX_V = n * m + 2;
        vector<Edge *> adj[MAX_V];

        int fieldTotal = 0;
        int S = n * m;
        int E = n * m + 1;
        Edge *e1;
        Edge *e2;

        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < m; ++j)
            {
                int val;
                cin >> val;
                fieldTotal += val;
                if ((i + j) % 2) // 짝짝, 홀홀
                {
                    e1 = new Edge(i * m + j, val);
                    e2 = new Edge(S, 0);
                    e1->dual = e2;
                    e2->dual = e1;
                    adj[S].push_back(e1);
                    adj[i * m + j].push_back(e2);

                    int dx[4] = {0, 0, 1, -1};
                    int dy[4] = {1, -1, 0, 0};
                    for (int k = 0; k < 4; ++k)
                    {
                        int y = i + dy[k];
                        int x = j + dx[k];
                        
                        if (x < 0 || x >= m || y < 0 || y >= n)
                            continue;

                        e1 = new Edge(y * m + x, INF);
                        e2 = new Edge(i * m + j, 0);
                        e1->dual = e2;
                        e2->dual = e1;
                        adj[i * m + j].push_back(e1);
                        adj[y * m + x].push_back(e2);
                    }
                }
                else
                {
                    e1 = new Edge(E, val);
                    e2 = new Edge(i * m + j, 0);
                    e1->dual = e2;
                    e2->dual = e1;
                    adj[i * m + j].push_back(e1);
                    adj[E].push_back(e2);
                }
            }
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

        cout << fieldTotal - total << '\n';
    }
}