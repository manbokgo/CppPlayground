// URL: https://www.acmicpc.net/problem/2609
// Algo: GCD, LCM, 유클리드 호제법(이지만 STL 쓰기)

// Start:	240213 00 40
// Read:	0 0
// Think:	0 0
// Code:	0 3
// Total:	0 3

#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define X first
#define Y second
#define all(x) x.begin(), x.end()
#define sortvec(x) sort(all(x))
#define compress(x) x.erase(unique(all(x)), x.end())
#define findvec(x, value) find(all(x), value) != x.end()

using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;

constexpr ll  MOD = 1000000007;
constexpr int INF = 0x3f3f3f3f;
constexpr ll  LLINF = 1e18;


int _gcd(int a, int b)
{
    return b ? _gcd(b, a % b) : a;
}

int _gcd2(int a, int b)
{
    int temp = a % b;
    while (temp != 0)
    {
        a = b;
        b = temp;
        temp = a % b;
    }

    return b;
}

int _lcm(int a, int b)
{
    return abs(a * b) / _gcd(a, b);
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int a, b;
    cin >> a >> b;

    // 몰라레후!
    // cout << gcd(a, b) << "\n" << lcm(a, b);
    cout << _gcd(a, b) << "\n" << _lcm(a, b);
}
