#include <bits/stdc++.h>
using namespace std;
const int MAX_V = 10000;
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

    for (int tc = 1;; ++tc)
    {
        int k, n;
        vector<Edge *> adj[MAX_V];
        cin >> k >> n;
        if (k == 0 && n == 0)
            return 0;

        int S = 1;
        int E = 2;
        Edge *e1;
        Edge *e2;

        for (int v = 0; v < n; ++v)
        {
            e1 = new Edge(v * 2 + 1, 1);
            e2 = new Edge(v * 2, 0);
            e1->dual = e2;
            e2->dual = e1;
            adj[v * 2].push_back(e1);
            adj[v * 2 + 1].push_back(e2);
        }

        cin.ignore(256, '\n');
        for (int i = 0; i < n; i++)
        {
            string s;
            getline(cin, s);
            stringstream ss(s);
            while (ss >> s)
            {
                int u = stoi(s) - 1;
                e1 = new Edge(u * 2, 1);
                e2 = new Edge(i * 2 + 1, 0);
                e1->dual = e2;
                e2->dual = e1;
                adj[i * 2 + 1].push_back(e1);
                adj[u * 2].push_back(e2);
            }
        }

        int total = 0;
        queue<int> pathAns;
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
                        {
                            break;
                        }
                    }
                }
            }
            if (prev[E] == -1)
                break;

            int flow = 1;
            for (int i = E; i != S; i = prev[i])
            {
                path[i]->addFlow(flow);
            }
            total++;
        }

        cout << "Case " << tc << ":\n";
        if (total >= k)
        {
            while (k > 0)
            {
                int cur = S;
                while (cur != E)
                {
                    int prev = cur;
                    for (Edge *e : adj[cur])
                    {
                        if (e->f > 0)
                        {
                            if (cur % 2 == 1)
                                cout << cur / 2 + 1 << " ";
                            e->f = 0;
                            cur = e->to;
                            break;
                        }
                    }
                }
                cout << "2\n";
                --k;
            }
        }
        else
        {
            cout << "Impossible\n";
        }
        cout << "\n";
    }
}