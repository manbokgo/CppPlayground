// URL: https://www.acmicpc.net/problem/11049
// Algo: DP

// Start:	240526 02 39
// Read:	0 1
// Think:	0 0
// Code:	0 3
// Total:	0 4

// LV3 12942 최적의 행렬 곱셈 복붙 날먹

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
constexpr int INF = 0x3f3f3f3f;
using pii = pair<int, int>;

int n;
pii mat[500];
int dp[500][500];

int DFS(int i, int j)
{
    if (dp[i][j] != -1) return dp[i][j];
    
    dp[i][j] = INF;
    for (int k = i; k < j; ++k)
        dp[i][j] = min(dp[i][j], DFS(i, k) + DFS(k+1, j) + mat[i].first * mat[k].second * mat[j].second);
    
    return dp[i][j];
}

int main()
{
    fastio;
    memset(dp, -1, sizeof(dp));
    for (int i = 0; i < 500; ++i)
        dp[i][i] = 0;

    cin >> n;
    for (int i = 0; i < n; ++i)
    {
        auto& [r, c] = mat[i];
        cin >> r >> c;
    }

    cout << DFS(0, n-1);
}
