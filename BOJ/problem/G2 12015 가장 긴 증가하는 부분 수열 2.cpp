﻿// URL: https://www.acmicpc.net/problem/12015
// Algo: DP LIS

// Start:	240220 00 38
// Read:	0 0
// Think:	0 0
// Code:	0 0
// Total:	0 0 연습용으로 푼 '가장 긴 증가하는 부분 수열' 문제랑 해결법이 동일함

#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define X first
#define Y second
#define all(x) x.begin(), x.end()
#define sortVec(x) sort(all(x))
#define compress(x) x.erase(unique(all(x)), x.end())
#define existInVec(x, value) find(all(x), value) != x.end()

using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using tiii = tuple<int, int, int>;

constexpr ll  MOD = 1000000007;
constexpr int INF = 0x3f3f3f3f;
constexpr ll  LLINF = 1e18;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

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
