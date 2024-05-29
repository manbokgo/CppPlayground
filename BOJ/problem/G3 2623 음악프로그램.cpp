// URL: https://www.acmicpc.net/problem/2623
// Algo: 위상 정렬

// Start:	240529 17 25
// Read:	0 1
// Think:	0 1
// Code:	0 5
// Total:	0 7

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) x.begin(), x.end()
#define pb push_back

vector<int> adj[1'001];
int indegree[1'001];

int main()
{
    fastio;

    int n, m;
    cin >> n >> m;

    for (int i = 0; i < m; ++i)
    {
        int cnt;
        cin >> cnt;

        int prv;
        cin >> prv;
        --cnt;

        while (cnt--)
        {
            int num;
            cin >> num;
            adj[prv].pb(num);
            ++indegree[num];
            prv = num;
        }
    }

    queue<int> q;
    for (int i = 1; i <= n; ++i)
    {
        if (indegree[i] == 0) q.push(i);
    }

    vector<int> answer;
    answer.reserve(n);
    while (!q.empty())
    {
        int cur = q.front();
        q.pop();
        answer.pb(cur);
        for (const int nxt : adj[cur])
        {
            --indegree[nxt];
            if (indegree[nxt] == 0) q.push(nxt);
        }
    }

    if (answer.size() != n) cout << 0;
    else for (const int num : answer) cout << num << '\n';
}
