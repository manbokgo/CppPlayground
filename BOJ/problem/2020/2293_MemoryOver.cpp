#include <bits/stdc++.h>

using namespace std;
const int INF = 1000000000;
int n;
int dp[101][10001];
int coin[101];

int solve(int num, int left)
{
    if (num == n)
        return (left == 0 ? 1 : 0);
    if (dp[num][left] != -1)
        return dp[num][left];

    int result = solve(num + 1, left);
    if (left >= coin[num])
        result += solve(num, left - coin[num]);
    dp[num][left] = result;
    return result;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int k;
    cin >> n >> k;

    for (int i = 0; i < n; i++)
    {
        cin >> coin[i];
    }

    // top-down
    // fill(*dp, *dp + sizeof(dp) / sizeof(int), -1);
    // cout << solve(0, k);

    // bottom-up
    // i 이전의 동전들 사용하여 충족하는 경우의 수
    fill(*dp, *dp + sizeof(dp) / sizeof(int), 0);
    for (int i = 0; i < n; i++)
    {
        dp[i][0] = 1;
        for (int j = 0; j <= k; j++)
        {
            dp[i + 1][j] += dp[i][j];
            int jj = j + coin[i];
            if (jj <= k)
                dp[i][jj] += dp[i][j];
        }
    }
    cout << dp[n-1][k];
}