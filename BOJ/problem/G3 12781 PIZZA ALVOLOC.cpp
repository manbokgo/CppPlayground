// URL: https://www.acmicpc.net/problem/12781
// Algo: CCW, 선분 교차 판정

// Start:	241117 05 34
// Read:	0 1
// Think:	0 1
// Code:	0 6
// Total:	0 8

// G3 17386 선분 교차 1 이랑 비슷한 문제. 단, 두 선분이 아예 동떨어져있는 경우는 없으며
// 완전히 교차하거나, 끝점만 교차하는 2가지 경우가 있다.

// 끝점만 교차하는 경우에는 4등분이 되지 않으므로, 완전히 교차하는 ret1 < 0 && ret2 < 0 조건만 맞도록 해야함

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

ll CCW(Pos p1, Pos p2, Pos p3) { return (p2.X - p1.X) * (p3.Y - p1.Y) - (p3.X - p1.X) * (p2.Y - p1.Y); }
int Normalize(ll var) { return var > 0 ? 1 : var < 0 ? -1 : 0; }

bool LineCrossed(Line l1, Line l2)
{
    const ll a = CCW(l1.p1, l1.p2, l2.p1);
    const ll b = CCW(l1.p1, l1.p2, l2.p2);
    const ll c = CCW(l2.p1, l2.p2, l1.p1);
    const ll d = CCW(l2.p1, l2.p2, l1.p2);

    const int ret1 = Normalize(a) * Normalize(b);
    const int ret2 = Normalize(c) * Normalize(d);

    if (ret1 < 0 && ret2 < 0) return true;
    else return false;
}

int main()
{
    fastio;

    Line l1, l2;
    cin >> l1.p1.X >> l1.p1.Y >> l1.p2.X >> l1.p2.Y
        >> l2.p1.X >> l2.p1.Y >> l2.p2.X >> l2.p2.Y;

    cout << LineCrossed(l1, l2);
}
