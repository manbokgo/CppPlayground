// URL: https://www.acmicpc.net/problem/1064
// Algo: 기하학

// Start:	241210 19 58
// Read:	0 1
// Think:	0 4
// Code:	0 13
// Total:	0 18

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) x.begin(), x.end()
#define pb push_back

int main()
{
    fastio;

    cout.precision(10);
    cout << fixed;

    int x1, y1, x2, y2, x3, y3;
    cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;

    // CCW
    if ((x2 - x1) * (y3 - y1) - (x3 - x1) * (y2 - y1) == 0)
    {
        cout << -1.0;
        return 0;
    }

    const double d1 = hypot(x2 - x1, y2 - y1);
    const double d2 = hypot(x3 - x1, y3 - y1);
    const double d3 = hypot(x3 - x2, y3 - y2);

    cout << 2 * (max({d1, d2, d3}) - min({d1, d2, d3}));
}
