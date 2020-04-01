// 위상 정렬
#include <bits/stdc++.h>
using namespace std;
const int MAX = 32000;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    vector<int> adj[MAX];
    int indegree[MAX] = {};
    cin >> n >> m;
    for (int i = 0; i < m; i++)
    {
        int u, v;
        cin >> u >> v;
        --u;
        --v;
        adj[u].push_back(v);
        ++indegree[v];
    }

    int sorted[MAX];
    queue<int> Q;
    for (int i = 0; i < n; i++)
        if (indegree[i] == 0)
            Q.push(i);

    for (int i = 0; i < n; i++)
    {
        if (Q.empty())
            return 0;

        int cur = Q.front();
        Q.pop();
        sorted[i] = cur + 1;
        for (auto&& next : adj[cur])
            if (--indegree[next] == 0)
                Q.push(next);
    }

    for (int i = 0; i < n; i++)
        cout << sorted[i] << " ";
}