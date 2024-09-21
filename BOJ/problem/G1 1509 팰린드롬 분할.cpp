// URL: https://www.acmicpc.net/problem/1509
// Algo: DP, 팰린드롬 기본

// Start:	240921 11 01
// Read:	0 1
// Think:	0 12
// Code:	0 11
// Total:	0 24

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) x.begin(), x.end()
#define pb push_back

constexpr int INF = 0x3f3f3f3f;

int dp[2501];
bool palin[2501][2501];

int main()
{
    fastio;
    memset(dp, INF, sizeof(dp));

    string str;
    str.push_back(0);

    string tmp;
    cin >> tmp;
    const int n = tmp.size();
    str += tmp;

    // 팰린드롬
    for (int i = 1; i <= n; ++i)
    {
        palin[i][i] = true;
        if (str[i] == str[i + 1])
            palin[i][i + 1] = true;
    }

    for (int len = 3; len <= n; ++len)
    {
        for (int i = 1, j = len; i <= n - len + 1; ++i, ++j)
        {
            if (palin[i + 1][j - 1] && str[i] == str[j])
            {
                palin[i][j] = true;
            }
        }
    }

    dp[0] = 0;
    dp[1] = 1;
    for (int i = 2; i <= n; i++)
    {
        for (int j = 1; j <= i; j++)
        {
            if (palin[j][i])
            {
                dp[i] = min(dp[i], dp[j - 1] + 1);
            }
        }
    }

    cout << dp[n];
}
