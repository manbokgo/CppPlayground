// URL: https://www.acmicpc.net/problem/1629
// Algo: 수학

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

ll a, b, c;

ll Solve(ll cur)
{
    if (cur == 0) return 1;
    if (cur == 1) return a % c;

    const ll half = Solve(cur / 2) % c;

    if (cur % 2 == 0) return half * half % c;
    else return half * half % c * a % c;
}

int main()
{
    cin >> a >> b >> c;
    cout << Solve(b);
}
