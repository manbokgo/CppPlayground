// URL: https://www.acmicpc.net/problem/10942
// Algo: DP

// Start:	240601 06 19
// Read:	0 1
// Think:	0 1
// Code:	0 3
// Total:	0 5

// LV3 12904 가장 긴 팰린드롬 문제에서의 DP 풀이법 거의 그대로 적용해서 날먹함

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) x.begin(), x.end()
#define pb push_back

int arr[2001];
bool dp[2001][2001];
int main()
{
    fastio;
    int n;
    cin >> n;
    for (int i = 1; i <= n; ++i)
        cin >> arr[i];

    for (int i = 1; i <= n; ++i)
    {
        dp[i][i] = true;
        if (arr[i] == arr[i + 1])
            dp[i][i + 1] = true;
    }

    for (int len = 3; len <= n; ++len)
    {
        for (int i = 1, j = len; i <= n - len + 1; ++i, ++j)
        {
            if (dp[i + 1][j - 1] && arr[i] == arr[j])
            {
                dp[i][j] = true;
            }
        }
    }

    int m;
    cin >> m;
    while (m--)
    {
        int a, b;
        cin >> a >> b;
        cout << dp[a][b] << '\n';
    }
}
