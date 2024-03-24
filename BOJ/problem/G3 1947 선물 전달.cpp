// URL: https://www.acmicpc.net/problem/1947
// Algo: DP

// Start:	240323 19 03
// Read:	0 0
// Think:	0 16
// Code:	0 13
// Total:	0 29

// 이런 경우를 '완전순열'이라고 한다.
// https://namu.wiki/w/%EC%99%84%EC%A0%84%EC%88%9C%EC%97%B4

#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define Y first
#define X second
#define all(x) x.begin(), x.end()
#define SortVec(x) sort(all(x))
#define CompressVec(x) x.erase(unique(all(x)), x.end())
#define ExistInVec(x, value) find(all(x), value) != x.end()

using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using tiii = tuple<int, int, int>;
using tlll = tuple<ll, ll, ll>;

constexpr int INF = 0x3f3f3f3f;

ll dp[1'000'001];
constexpr ll MOD = 1'000'000'000;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    dp[1] = 0;
    dp[2] = 1;
    for (ll i = 3; i <= n; ++i)
    {
        dp[i] = (i - 1) * (dp[i-1] + dp[i-2]) % MOD;
    }

    cout << dp[n];
}
