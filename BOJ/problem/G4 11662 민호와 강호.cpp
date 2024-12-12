// URL: https://www.acmicpc.net/problem/11662
// Algo: 삼분 탐색 (실수)

// Start:	241213 08 01
// Read:	0 2
// Think:	0 15
// Code:	0 10
// Total:	0 27

// G5 11664 선분과 점 문제와 거의 비슷하다.
// 아래로 볼록한(유니모달한) 함수인지는 직관적으로 알 것 같긴 해도 좀 애매했는데 맞긴 맞았다.

// https://mslim8803.tistory.com/13
// 미분해서 도함수로 증명한 사람도 있다.

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) x.begin(), x.end()
#define pb push_back

double Lerp(double a, double b, double t)
{
    return a + t * (b - a);
}

double GetDistSquare(double x1, double y1, double x2, double y2)
{
    return (x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1);
}

int main()
{
    fastio;

    cout.precision(7);
    cout << fixed;

    double ax, ay, bx, by, cx, cy, dx, dy;
    cin >> ax >> ay >> bx >> by >> cx >> cy >> dx >> dy;

    double lo = 0;
    double hi = 1;

    while (hi - lo >= 1e-7)
    {
        const double mid1 = (lo * 2 + hi) / 3;
        const double mid2 = (lo + hi * 2) / 3;

        const double dist1 = GetDistSquare(Lerp(ax, bx, mid1), Lerp(ay, by, mid1),
            Lerp(cx, dx, mid1), Lerp(cy, dy, mid1));

        const double dist2 = GetDistSquare(Lerp(ax, bx, mid2), Lerp(ay, by, mid2),
            Lerp(cx, dx, mid2), Lerp(cy, dy, mid2));

        if (dist1 > dist2) lo = mid1;
        else hi = mid2;
    }

    cout << sqrt(GetDistSquare(Lerp(ax, bx, lo), Lerp(ay, by, lo),
        Lerp(cx, dx, lo), Lerp(cy, dy, lo)));
}
