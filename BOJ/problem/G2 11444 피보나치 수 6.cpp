// URL: https://www.acmicpc.net/problem/11444
// Algo: 수학

// Start:	250116 08 06
// Read:	0 1
// Think:	0 24
// Code:	0 5
// Total:   0 30

// 거듭제곱 풀이 https://velog.io/@junttang/BOJ-11444-%ED%94%BC%EB%B3%B4%EB%82%98%EC%B9%98-%EC%88%98-6-%ED%95%B4%EA%B2%B0-%EC%A0%84%EB%9E%B5-C
// 행렬 풀이 https://blogshine.tistory.com/274

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) x.begin(), x.end()
#define pb push_back

using ll = long long;
constexpr ll MOD = 1000000007;

unordered_map<ll, ll> dp;

ll Fibonacci(ll num)
{
    if (dp.count(num)) return dp[num];

    if (num % 2 == 0)
    {
        const ll half = Fibonacci(num / 2);
        const ll halfM1 = Fibonacci(num / 2 - 1);
        dp[num] = (half * (2LL * halfM1 + half)) % MOD;
    }
    else
    {
        const ll halfP1 = Fibonacci((num + 1) / 2);
        const ll halfM1 = Fibonacci((num - 1) / 2);
        dp[num] = (halfP1 * halfP1 + halfM1 * halfM1) % MOD;
    }

    return dp[num];
}

int main()
{
    fastio;

    dp[0] = 0;
    dp[1] = 1;
    dp[2] = 1;

    ll n;
    cin >> n;
    cout << Fibonacci(n);
}
