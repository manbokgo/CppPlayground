// URL: https://www.acmicpc.net/problem/2533
// Algo: 트리 DP

// Start:	240925 20 04
// Read:	0 1
// Think:	0 9
// Code:	0 6
// Total:	0 16

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) x.begin(), x.end()
#define pb push_back

int n;
vector<int> adj[1'000'001];
int dp[1'000'001][2]; // 본인이 (0:일반인 1:얼리어답터)일 때 서브트리의 얼리어답터 최소 수

void DFS(int cur, int parent)
{
    dp[cur][0] = 0;
    dp[cur][1] = 1;

    for (const int nxt : adj[cur])
    {
        if (nxt == parent) continue;

        DFS(nxt, cur);
        dp[cur][1] += min(dp[nxt][0], dp[nxt][1]);
        dp[cur][0] += dp[nxt][1];
    }
}

int main()
{
    fastio;
    cin >> n;
    for (int i = 0; i < n - 1; ++i)
    {
        int a, b;
        cin >> a >> b;
        adj[a].pb(b);
        adj[b].pb(a);
    }

    DFS(1, -1);
    cout << min(dp[1][0], dp[1][1]);
}
