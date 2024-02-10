#include <bits/stdc++.h>

#define pb push_back
#define mp make_pair
#define F first
#define S second
#define all(x) x.begin(), x.end()
#define sortvec(x) sort(all(x))
#define compress(x) x.erase(unique(all(x)), x.end())
#define findvec(x, value) find(all(x), value) != x.end()

using namespace std;
bool visit[1001];

void dfs(vector<int> *vec, int start)
{
    visit[start] = true;
    cout << start << " ";
    for (auto &&i : vec[start])
    {
        if (!visit[i])
            dfs(vec, i);
    }
}

void dfsWithStack(vector<int> *vec, int start)
{
    stack<int> S;
    S.push(start);
    visit[start] = true;
    cout << start << " ";

    while (!S.empty())
    {
        int cur = S.top();
        S.pop();

        for (auto &&i : vec[cur])
        {
            if (!visit[i])
            {
                cout << i << " ";
                S.push(cur);
                S.push(i);
                visit[i] = true;
                break;
            }
        }
    }
}

void bfs(vector<int> *vec, int start)
{
    queue<int> Q;
    Q.push(start);
    visit[start] = true;

    while (!Q.empty())
    {
        int cur = Q.front();
        Q.pop();
        cout << cur << " ";

        for (auto &&i : vec[cur])
        {
            if (!visit[i])
            {
                Q.push(i);
                visit[i] = true;
            }
        }
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, v;
    cin >> n >> m >> v;
    vector<int> adj[n + 1];

    for (int i = 0; i < m; i++)
    {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    for (int i = 1; i <= n; i++)
    {
        sortvec(adj[i]);
    }

    fill(visit, visit + 1001, false);
    dfs(adj, v);
    // dfsWithStack(adj, v);
    cout << "\n";

    fill(visit, visit + 1001, false);
    bfs(adj, v);
    cout << "\n";
}