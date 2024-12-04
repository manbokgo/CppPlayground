// URL: https://www.acmicpc.net/problem/7869
// Algo: 기하학 (활꼴의 넓이)

// Start:	241204 14 00
// Read:	0 1
// Think:	0 34
// Code:	0 9
// Total:   0 44

// https://lighter.tistory.com/136

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) x.begin(), x.end()
#define pb push_back

int main()
{
    fastio;

    constexpr double pi = 3.141592653589793238463;
    cout.precision(3);
    cout << fixed;

    double x1, y1, r1, x2, y2, r2;
    cin >> x1 >> y1 >> r1 >> x2 >> y2 >> r2;

    const double dist = sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
    const double sub = abs(r2 - r1);
    const double plu = abs(r2 + r1);


    if (plu <= dist) // 겹치지 않음
    {
        cout << 0.000;
        return 0;
    }

    if (dist <= sub) // 포함. 작은 원 넓이 출력.
    {
        cout << min(r1 * r1 * pi, r2 * r2 * pi);
        return 0;
    }

    const double theta1 = 2 * acos((dist * dist + r1 * r1 - r2 * r2) / (2 * r1 * dist));
    const double theta2 = 2 * acos((dist * dist + r2 * r2 - r1 * r1) / (2 * r2 * dist));

    const double sz1 = r1 * r1 * (theta1 - sin(theta1)) / 2;
    const double sz2 = r2 * r2 * (theta2 - sin(theta2)) / 2;

    cout << sz1 + sz2;
}
