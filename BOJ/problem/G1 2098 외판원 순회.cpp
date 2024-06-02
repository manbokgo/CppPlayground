// URL: https://www.acmicpc.net/problem/2098
// Algo: 외판원 순회 기본

// Start:	
// Read:	0 2
// Think:	0 3
// Code:	0 5
// Total:	0 10

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) x.begin(), x.end()
#define pb push_back

constexpr int INF = 0x3f3f3f3f;

int n;
int adj[16][16];
int dp[16][1<<16];


int DFS(int cur, int visited)
{
    if (visited == (1 << n) - 1) // 전체 방문
        return adj[cur][0];

    if (dp[cur][visited] != -1)
        return dp[cur][visited];

    dp[cur][visited] = INF;
    for (int i = 0; i < n; ++i)
    {
        if (adj[cur][i] == INF) continue;
        if (visited & 1 << i) continue;
        dp[cur][visited] = min(dp[cur][visited], adj[cur][i] + DFS(i, visited | 1 << i));
    }
    return dp[cur][visited];
}

int main()
{
    fastio;
    memset(dp, -1, sizeof(dp));

    cin >> n;
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            cin >> adj[i][j];
            if (adj[i][j] == 0) adj[i][j] = INF;
        }
    }

    cout << DFS(0, 1);
}
