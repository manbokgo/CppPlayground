// URL: https://www.acmicpc.net/problem/13172
// Algo: 수학, 분할 정복 거듭 제곱, 모듈러 곱셈 역원, 페르마의 소정리

// Start:	250119 08 50
// Read:	0 3
// Think:	0 7
// Code:	0 12
// Total:   0 22

// 문제가 매우 길지만 핵심은 소수 모듈러에 한하여 b^MOD-2 = b^-1 (mod X) 와 동일하다는 것.
// 이때 b^-1 은 모듈러 곱셈 역원이다.

// S1 1629 곱셈 의 방식대로 분할 정복을 이용하여 1,000,000,005 승을 O(logn)으로 계산해 b^-1을 구하고,
// 문제에서 원하는대로 a * b^-1 mod X 를 구한다.

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) x.begin(), x.end()
#define pb push_back

using ll = long long;
constexpr ll MOD = 1000000007;

ll Power(ll x, ll y)
{
    if (y == 1) return x % MOD;
    if (y % 2 == 1) return Power(x, y - 1) * x % MOD;

    const ll half = Power(x, y / 2);
    return half * half % MOD;
}

int main()
{
    fastio;

    int m;
    cin >> m;

    ll ans = 0;
    while (m--)
    {
        ll a, b;
        cin >> b >> a;

        const ll g = gcd(a, b);
        a /= g;
        b /= g;

        ans += a * Power(b, MOD - 2) % MOD;
        ans %= MOD;
    }

    cout << ans;
}
