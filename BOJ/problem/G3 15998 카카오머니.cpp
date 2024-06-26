// URL: https://www.acmicpc.net/problem/15998
// Algo: 수학, GCD

// Start:	240626 16 05
// Read:	0 4
// Think:	0 12
// Code:	0 31
// Total:	0 47

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) x.begin(), x.end()
#define pb push_back

using ll = long long;

int main()
{
    fastio;

    int n;
    cin >> n;

    ll prv = 0;
    ll M = -1;
    ll maxCur = -1;

    while (n--)
    {
        ll a, cur;
        cin >> a >> cur;

        if (prv + a < 0)
        {
            const ll charge = cur - (prv + a);

            if (M == -1) M = charge;
            else M = gcd(M, charge);

            maxCur = max(maxCur, cur);
            if (M <= maxCur)
            {
                cout << -1;
                return 0;
            }
        }
        else
        {
            if (prv + a != cur)
            {
                cout << -1;
                return 0;
            }
        }

        prv = cur;
    }

    if (M == -1) M = 1;
    cout << M;
}
