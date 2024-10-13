// URL: https://www.acmicpc.net/problem/12869
// Algo: DP

// Start:	241013 19 09
// Read:	0 1
// Think:	0 6
// Code:	0 10
// Total:	0 17

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) x.begin(), x.end()
#define pb push_back

using tiii = tuple<int, int, int>;
constexpr int INF = 0x3f3f3f3f;

int arr[3];
int dp[61][61][61];
auto cases = {
    tiii
    {9, 3, 1},
    {9, 1, 3},
    {3, 9, 1},
    {1, 9, 3},
    {3, 1, 9},
    {1, 3, 9},
};

int DFS(int a, int b, int c)
{
    if (a < 0) return DFS(0, b, c);
    if (b < 0) return DFS(a, 0, c);
    if (c < 0) return DFS(a, b, 0);
    if (dp[a][b][c] != -1) return dp[a][b][c];

    dp[a][b][c] = INF;
    for (const auto& [t1, t2, t3] : cases)
        dp[a][b][c] = min(dp[a][b][c], DFS(a - t1, b - t2, c - t3) + 1);

    return dp[a][b][c];
}

int main()
{
    fastio;
    memset(dp, -1, sizeof(dp));
    dp[0][0][0] = 0;

    int n;
    cin >> n;
    for (int i = 0; i < n; ++i)
        cin >> arr[i];

    cout << DFS(arr[0], arr[1], arr[2]);
}
