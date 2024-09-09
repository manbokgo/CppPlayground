// URL: https://www.acmicpc.net/problem/1766
// Algo: 위상 정렬, 우선순위 큐

// Start:	240909 23 00
// Read:	0 1
// Think:	0 0
// Code:	0 2
// Total:	0 3

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) x.begin(), x.end()
#define pb push_back

int indegree[32'001];
vector<int> adj[32'001];

int main()
{
    fastio;

    int n, m;
    cin >> n >> m;
    while (m--)
    {
        int a, b;
        cin >> a >> b;
        adj[a].pb(b);
        ++indegree[b];
    }

    priority_queue<int, vector<int>, greater<>> pq;
    for (int i = 1; i <= n; ++i)
    {
        if (indegree[i] == 0)
        {
            pq.push(i);
        }
    }

    while (!pq.empty())
    {
        int cur = pq.top();
        pq.pop();

        cout << cur << ' ';

        for (auto nxt : adj[cur])
        {
            --indegree[nxt];
            if (indegree[nxt] == 0)
            {
                pq.push(nxt);
            }
        }
    }
}
