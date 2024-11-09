// URL: https://www.acmicpc.net/problem/2022
// Algo: 수학, 기하학, 이분 탐색

// Start:	241109 18 00
// Read:	0 1
// Think:	0 20
// Code:	0 5
// Total:	0 26

// 거의 다 생각해냈는데... 결국 패배하고 블로그 봄. 좀만 더 생각해볼 걸.
// https://sw-ko.tistory.com/145

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) x.begin(), x.end()
#define pb push_back

int main()
{
    fastio;

    double x, y, c;
    cin >> x >> y >> c;

    double lo = 0;
    double hi = min(x, y);

    while (hi - lo > 0.000001)
    {
        const double mid = (lo + hi) / 2.0;

        const double h1 = sqrt(x * x - mid * mid);
        const double h2 = sqrt(y * y - mid * mid);
        const double ret = (h1 * h2) / (h1 + h2);

        if (ret >= c) lo = mid;
        else hi = mid;
    }

    cout.precision(3);
    cout << fixed << lo;
}
