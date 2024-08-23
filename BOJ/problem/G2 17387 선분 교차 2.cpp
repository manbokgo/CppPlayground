// URL: https://www.acmicpc.net/problem/17387
// Algo: CCW, 선분 교차 판정

// Start:	240728 05 02
// Read:	0 3
// Think:	0 41
// Code:	0 14
// Total:	0 58

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
    const int ret1 = Normalize(CCW(l1.p1, l1.p2, l2.p1)) * Normalize(CCW(l1.p1, l1.p2, l2.p2));
    const int ret2 = Normalize(CCW(l2.p1, l2.p2, l1.p1)) * Normalize(CCW(l2.p1, l2.p2, l1.p2));

    if (ret1 > 0 || ret2 > 0) return false;
    if (ret1 < 0 || ret2 < 0) return true;

    // 일직선 혹은 한 점 ret1 == 0 && ret2 == 0
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
