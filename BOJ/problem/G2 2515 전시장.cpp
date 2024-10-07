// URL: https://www.acmicpc.net/problem/2515
// Algo: DP

// Start:	241007 17 32
// Read:	0 2
// Think:	0 14
// Code:	0 7
// Total:	0 23

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) x.begin(), x.end()
#define pb push_back

using pii = pair<int, int>;

pii arr[300'001];
int dp[300'001];
int lim[300'001];


int main()
{
    fastio;

    int n, mxLim;
    cin >> n >> mxLim;
    for (int i = 1; i <= n; ++i)
    {
        auto& [a, b] = arr[i];
        cin >> a >> b;
    }
    sort(arr + 1, arr + 1 + n);

    for (int i = 1; i <= n; ++i)
    {
        const auto [curH, curV] = arr[i];
        for (lim[i] = lim[i - 1]; lim[i] < i; ++lim[i])
        {
            if (arr[lim[i]].first + mxLim > curH)
            {
                break;
            }
        }
        --lim[i];
    }

    for (int i = 1; i <= n; ++i)
    {
        dp[i] = max(dp[i - 1], dp[lim[i]] + arr[i].second);
    }
    cout << dp[n];
}
