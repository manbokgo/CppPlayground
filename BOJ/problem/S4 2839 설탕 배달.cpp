// URL: https://www.acmicpc.net/problem/2839
// Algo: 그리디

// Start:	241130 13 09
// Read:	0 1
// Think:	0 1
// Code:	0 4
// Total:	0 6

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) x.begin(), x.end()
#define pb push_back

int main()
{
    fastio;

    int n;
    cin >> n;

    int ans = 0;
    while (n >= 0)
    {
        if (n % 5 == 0)
        {
            ans += n / 5;
            cout << ans;
            return 0;
        }
        n -= 3;
        ++ans;
    }
    cout << -1;
}
