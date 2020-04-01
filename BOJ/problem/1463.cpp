#include <bits/stdc++.h>

using namespace std;
const int MAX = 1000001;
int dp[MAX];

int solve(int n)
{
    if (n == 1)
        return 0;
    if (dp[n] != -1)
        return dp[n];

    int result = solve(n - 1) + 1;
    if (n % 3 == 0)
    {
        result = min(result, solve(n / 3) + 1);
    }
    if (n % 2 == 0)
    {
        result = min(result, solve(n / 2) + 1);
    }
    dp[n] = result;
    return result;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    // top-down
    // fill(dp, dp + MAX, -1);
    // cout << solve(n);

    // bottom-up
    fill(dp, dp + MAX, 100000000);
    dp[1] = 0;
    for (int i = 1; i < n; i++)
    {
        dp[i + 1] = min(dp[i + 1], dp[i] + 1);
        if (i * 2 < MAX)
            dp[i * 2] = min(dp[i * 2], dp[i] + 1);
        if (i * 3 < MAX)
            dp[i * 3] = min(dp[i * 3], dp[i] + 1);
    }
    cout << dp[n];
}