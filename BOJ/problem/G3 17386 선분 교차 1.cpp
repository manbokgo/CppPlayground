// URL: https://www.acmicpc.net/problem/17386
// Algo: CCW, 선분 교차 판정

// Start:	240818 10 23
// Read:	0 1
// Think:	0 0
// Code:	0 0
// Total:	0 1 G2 17387 선분교차2 복붙 날먹

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) x.begin(), x.end()
#define pb push_back
#define X first
#define Y second

using ll = long long;
using Pos = pair<ll, ll>;
struct Line
{
    Pos p1;
    Pos p2;
};

ll CCW(Pos p1, Pos p2, Pos p3)
{
    // return (p2.X - p1.X) * (p3.Y - p1.Y) - (p3.X - p1.X) * (p2.Y - p1.Y);
    ll ret = (p2.X - p1.X) * (p3.Y - p1.Y) - (p3.X - p1.X) * (p2.Y - p1.Y);
    return clamp(ret, -1LL, 1LL);
}

bool LineCrossed(Line l1, Line l2)
{
    const ll ret1 = CCW(l1.p1, l1.p2, l2.p1) * CCW(l1.p1, l1.p2, l2.p2);
    const ll ret2 = CCW(l2.p1, l2.p2, l1.p1) * CCW(l2.p1, l2.p2, l1.p2);

    if (ret1 > 0 || ret2 > 0) return false;
    if (ret1 < 0 || ret2 < 0) return true;

    // 일직선 ret1 == 0 && ret2 == 0
    if (l1.p1 > l1.p2) swap(l1.p1, l1.p2);
    if (l2.p1 > l2.p2) swap(l2.p1, l2.p2);

    if (l1.p2 < l2.p1 || l1.p1 > l2.p2) return false;
    else return true;
}

int main()
{
    fastio;

    Line l1, l2;
    cin >> l1.p1.X >> l1.p1.Y >> l1.p2.X >> l1.p2.Y
        >> l2.p1.X >> l2.p1.Y >> l2.p2.X >> l2.p2.Y;

    cout << LineCrossed(l1, l2);
}
