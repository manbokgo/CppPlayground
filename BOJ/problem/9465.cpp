#include <bits/stdc++.h>

using namespace std;
const int MAX = 1000001;

int n;
int dp[MAX][3];
// 0 왼쪽 안 뗌, 1 왼쪽 위 뗌, 2, 왼쪽 아래 뗌.
int value[MAX][2];

int solve(int c, int status)
{
    if (c == n)
        return 0;
    if (dp[c][status] != -1)
        return dp[c][status];

    int result = solve(c + 1, 0);
    if (status != 1)
        result = max(result, solve(c + 1, 1) + value[c][0]);
    if (status != 2)
        result = max(result, solve(c + 1, 2) + value[c][1]);
    dp[c][status] = result;
    return result;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--)
    {
        cin >> n;

        for (int i = 0; i < 2; i++)
        {
            for (int j = 0; j < n; j++)
            {
                cin >> value[j][i];
            }
        }
        
        // top-down
        // fill(*dp, *dp + sizeof(dp) / sizeof(int), -1);
        // cout << solve(0, 0) << "\n";

        // bottom-up
        fill(*dp, *dp + sizeof(dp) / sizeof(int), 0);
        for (int i = 0; i < n; i++)
        {
            dp[i + 1][0] = max(dp[i + 1][0], max(dp[i][0], max(dp[i][1], dp[i][2])));
            dp[i + 1][1] = max(dp[i + 1][1], max(dp[i][0], dp[i][2]) + value[i][0]);
            dp[i + 1][2] = max(dp[i + 1][2], max(dp[i][0], dp[i][1]) + value[i][1]);
        }
        cout << max(dp[n][0], max(dp[n][1], dp[n][2])) << "\n";
    }
}