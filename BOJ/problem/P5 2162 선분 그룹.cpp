// URL: https://www.acmicpc.net/problem/2162
// Algo: CCW, 선분 교차 판정, 분리 집합

// Start:	240920 09 14
// Read:	0 1
// Think:	0 1
// Code:	0 8
// Total:	0 10

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


int n;
Line lines[3'000];
int p[3'000];


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

    // 일직선상 혹은 끝점 겹침 ret1 == 0 && ret2 == 0
    if (l1.p1 > l1.p2) swap(l1.p1, l1.p2);
    if (l2.p1 > l2.p2) swap(l2.p1, l2.p2);

    if (l1.p2 < l2.p1 || l1.p1 > l2.p2) return false;
    else return true;
}

int Find(int a)
{
    if (p[a] < 0) return a;
    return p[a] = Find(p[a]);
}

bool Union(int a, int b)
{
    int ap = Find(a);
    int bp = Find(b);

    if (ap == bp) return false;
    if (-p[ap] < -p[bp]) swap(ap, bp);

    p[ap] += p[bp];
    p[bp] = ap;
    return true;
}

int main()
{
    fastio;
    memset(p, -1, sizeof(p));

    cin >> n;
    for (int i = 0; i < n; ++i)
    {
        cin >> lines[i].p1.X >> lines[i].p1.Y >> lines[i].p2.X >> lines[i].p2.Y;
    }

    for (int i = 0; i < n; ++i)
    {
        for (int j = i + 1; j < n; ++j)
        {
            if (Find(i) == Find(j)) continue;
            if (LineCrossed(lines[i], lines[j])) Union(i, j);
        }
    }

    int cnt = 0;
    int mxSz = 0;
    for (int i = 0; i < n; ++i)
    {
        if (p[i] < 0)
        {
            ++cnt;
            mxSz = max(mxSz, -p[i]);
        }
    }

    cout << cnt << '\n' << mxSz;
}
