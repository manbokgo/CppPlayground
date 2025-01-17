// URL: https://www.acmicpc.net/problem/16953
// Algo: 그리디

// Start:	250117 09 11
// Read:	0 1
// Think:	0 1
// Code:	0 5
// Total:	0 7

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) x.begin(), x.end()
#define pb push_back

int main()
{
    fastio;

    int a, b;
    cin >> a >> b;

    int ans = 1;
    while (b > a)
    {
        if (b % 10 == 1) b /= 10;
        else if (b % 2 == 0) b /= 2;
        else break;

        ++ans;
    }

    if (b == a) cout << ans;
    else cout << -1;
}
