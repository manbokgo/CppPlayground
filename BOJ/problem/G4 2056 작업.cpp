// URL: https://www.acmicpc.net/problem/2056
// Algo: 위상 정렬, DP

// Start:	240725 17 12
// Read:	0 2
// Think:	0 1
// Code:	0 7
// Total:	0 10

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) x.begin(), x.end()
#define pb push_back

int cost[10'001];
int dp[10'001];
int indegree[10'001];
vector<int> adj[10'001];

int main()
{
    fastio;

    int n;
    cin >> n;
    for (int i = 1; i <= n; ++i)
    {
        cin >> cost[i] >> indegree[i];
        for (int j = 0; j < indegree[i]; ++j)
        {
            int num;
            cin >> num;
            adj[num].pb(i);
        }
    }

    queue<int> q;
    for (int i = 1; i <= n; ++i)
    {
        if (indegree[i] == 0)
        {
            q.push(i);
            dp[i] = cost[i];
        }
    }

    while (!q.empty())
    {
        const int cur = q.front();
        q.pop();

        for (const int nxt : adj[cur])
        {
            dp[nxt] = max(dp[nxt], dp[cur] + cost[nxt]);
            --indegree[nxt];
            if (indegree[nxt] == 0) q.push(nxt);
        }
    }

    cout << *max_element(dp + 1, dp + n + 1);
}
