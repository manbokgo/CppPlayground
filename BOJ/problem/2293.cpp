#include <bits/stdc++.h>

using namespace std;

int n;
int dp[10001];
int coin[101];

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

    // bottom-up
    // i 이전의 동전들 사용하여 충족하는 경우의 수
    fill(dp, dp + sizeof(dp) / sizeof(int), 0);
    dp[0] = 1;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j <= k; j++)
        {
            if (j >= coin[i])
                dp[j] += dp[j - coin[i]];
        }
    }
    cout << dp[k];
}