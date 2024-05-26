// URL: https://www.acmicpc.net/problem/1005
// Algo: 위상 정렬, DP

// Start:	240527 03 36
// Read:	0 2
// Think:	0 1
// Code:	0 8
// Total:	0 11

// G3 1516 게임 개발 문제와 비슷했다

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) x.begin(), x.end()
#define pb push_back

vector<int> adj[1001];
int dp[1001];
int cost[1001];
int indegree[1001];

void Solve()
{
    for (auto& ad : adj) ad.clear();
    memset(dp, -1, sizeof(dp));
    memset(indegree, 0, sizeof(indegree));

    int n, k;
    cin >> n >> k;
    for (int i = 1; i <= n; ++i)
    {
        cin >> cost[i];
    }

    for (int i = 1; i <= k; ++i)
    {
        int a, b;
        cin >> a >> b;
        adj[a].pb(b);
        ++indegree[b];
    }

    int target;
    cin >> target;

    queue<int> q;
    for (int i = 1; i <= n; ++i)
    {
        if (indegree[i] != 0) continue;
        dp[i] = cost[i];
        q.push(i);
        if (i == target)
        {
            cout << dp[i] << '\n';
            return;
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
            if (indegree[nxt] == 0)
            {
                q.push(nxt);
                if (nxt == target)
                {
                    cout << dp[nxt] << '\n';
                    return;
                }
            }
        }
    }
}

int main()
{
    fastio;

    int T;
    cin >> T;

    while (T--)
    {
        Solve();
    }
}
