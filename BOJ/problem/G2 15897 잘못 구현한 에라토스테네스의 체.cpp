// URL: https://www.acmicpc.net/problem/15897
// Algo: 수학, 정수론

// Start:	240513 22 07
// Read:	0 2
// Think:	0 17
// Code:	0 7
// Total:	0 26

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
using ll = long long;

int main()
{
    fastio;

    ll n;
    cin >> n;

    ll answer = 0;
    ll lst = n;
    for (ll i = 1; i <= n;)
    {
        ll tmp = (n - 1) / i;
        answer += (lst - tmp) * i;
        if (tmp == 0) break;

        lst = tmp;
        ll md = (n-1) % i;
        i += md / tmp + 1;
    }

    cout << answer;
}
