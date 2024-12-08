// URL: https://www.acmicpc.net/problem/6439
// Algo: 선분 교차 판정

// Start:	241208 08 52
// Read:	0 2
// Think:	0 5
// Code:	0 14
// Total:	0 21

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

    if (ret1 > 0 || ret2 > 0) return false;
    if (ret1 < 0 || ret2 < 0) return true;

    if (l1.p1 > l1.p2) swap(l1.p1, l1.p2);
    if (l2.p1 > l2.p2) swap(l2.p1, l2.p2);

    if (l1.p2 < l2.p1 || l1.p1 > l2.p2) return false;
    else return true;
}

int main()
{
    fastio;

    int T;
    cin >> T;

    while (T--)
    {
        Line l1;
        cin >> l1.p1.X >> l1.p1.Y >> l1.p2.X >> l1.p2.Y;

        int tmpx1, tmpy1, tmpx2, tmpy2;
        cin >> tmpx1 >> tmpy1 >> tmpx2 >> tmpy2;

        int x1 = min(tmpx1, tmpx2);
        int x2 = max(tmpx1, tmpx2);
        int y1 = min(tmpy1, tmpy2);
        int y2 = max(tmpy1, tmpy2);

        if ((x1 <= l1.p1.X && l1.p1.X <= x2 && y1 <= l1.p1.Y && l1.p1.Y <= y2) &&
            (x1 <= l1.p2.X && l1.p2.X <= x2 && y1 <= l1.p2.Y && l1.p2.Y <= y2))
        {
            cout << "T\n";
            continue;
        }

        if ((LineCrossed(l1, {{x1, y1}, {x2, y1}})) ||
            (LineCrossed(l1, {{x2, y1}, {x2, y2}})) ||
            (LineCrossed(l1, {{x2, y2}, {x1, y2}})) ||
            (LineCrossed(l1, {{x1, y2}, {x1, y1}})))
        {
            cout << "T\n";
            continue;
        }

        cout << "F\n";
    }
}
