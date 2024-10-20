// URL: https://www.acmicpc.net/problem/12738
// Algo: DP (LIS)

// Start:	241020 11 12
// Read:	0 1
// Think:	0 0
// Code:	0 0
// Total:	0 1

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) x.begin(), x.end()
#define pb push_back

constexpr int INF = 0x3f3f3f3f;

int main()
{
    fastio;

    int n;
    cin >> n;

    vector<int> seq(n);
    vector<int> dp(n, INF);

    for (int i = 0; i < n; ++i)
    {
        cin >> seq[i];
        int idx = lower_bound(all(dp), seq[i]) - dp.begin();
        dp[idx] = seq[i];
    }
    const int LIS = lower_bound(all(dp), INF) - dp.begin();

    cout << LIS;
}
