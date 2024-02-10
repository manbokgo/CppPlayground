#include <bits/stdc++.h>

using namespace std;
const int INF = 1000000000;
int n;
int dp[101][10001];
int coin[101];

int solve(int num, int left)
{
    if (num == n)
        return (left == 0 ? 0 : INF);
    if (dp[num][left] != -1)
        return dp[num][left];

    int result = solve(num + 1, left);
    if (left >= coin[num])
        result = min(result, solve(num, left - coin[num]) + 1);
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
    // i 이후의 동전들 사용하는 개수
    // fill(*dp, *dp + sizeof(dp) / sizeof(int), -1);
    // int result = solve(0, k);
    // if (result == INF)
    //     cout << "-1";
    // else
    //     cout << result;

    // bottom-up
    // i 이전의 동전들 사용하는 개수
    fill(*dp, *dp + sizeof(dp) / sizeof(int), INF);
    for (int i = 0; i < n; i++)
    {
        dp[i][0] = 0;
        for (int j = 0; j <= k; j++)
        {
            dp[i + 1][j] = min(dp[i + 1][j], dp[i][j]);
            int jj = j + coin[i];
            if (jj <= k)
                dp[i][jj] = min(dp[i][jj], dp[i][j] + 1);
        }
    }
    int result = dp[n - 1][k];
    if (result == INF)
        cout << "-1";
    else
        cout << result;
}