// URL: https://www.acmicpc.net/problem/1629
// Algo: 수학, 분할 정복 거듭 제곱

// Start:	250115 07 47
// Read:	0 1
// Think:	0 5
// Code:	0 4
// Total:	0 10

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) x.begin(), x.end()
#define pb push_back

using ll = long long;

ll MOD;

ll Power(ll x, ll y)
{
    if (y == 1) return x % MOD;
    if (y % 2 == 1) return Power(x, y - 1) * x % MOD;

    const ll half = Power(x, y / 2);
    return half * half % MOD;
}

int main()
{
    ll a, b;
    cin >> a >> b >> MOD;
    cout << Power(a, b);
}
