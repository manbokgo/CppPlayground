// URL: https://www.acmicpc.net/problem/9240
// Algo: 회전하는 캘리퍼스 기본, 볼록 껍질

// Start:	241221 04 44
// Read:	0 1
// Think:	0 5
// Code:	0 48
// Total:   0 54

// 회전하는 캘리퍼스
// https://blog.naver.com/kks227/220857597424
// https://wondangcom.tistory.com/2683 (그림만 참고. 코드는 CCW 부등호 잘못 됨)

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) x.begin(), x.end()
#define pb push_back
#define X first
#define Y second

using ll = long long;
using Pos = pair<ll, ll>;

ll CCW(Pos p1, Pos p2, Pos p3) { return (p2.X - p1.X) * (p3.Y - p1.Y) - (p3.X - p1.X) * (p2.Y - p1.Y); }
int Normalize(ll var) { return var > 0 ? 1 : var < 0 ? -1 : 0; }

ll Square(ll num) { return num * num; }
ll GetDistSquare(Pos p1, Pos p2) { return Square(p1.X - p2.X) + Square(p1.Y - p2.Y); }

vector<Pos> MakeConvex(vector<Pos>& p)
{
    sort(p.begin(), p.end());
    sort(p.begin() + 1, p.end(), [pivot = p[0]](const Pos& a, const Pos& b)
    {
        const ll c = CCW(pivot, a, b);
        if (c == 0) return GetDistSquare(pivot, a) < GetDistSquare(pivot, b);
        return c > 0;
    });

    vector<Pos> convex;
    convex.push_back(p[0]);
    convex.push_back(p[1]);

    for (int i = 2; i < p.size(); ++i)
    {
        while (convex.size() >= 2 &&
            CCW(convex[convex.size() - 2], convex[convex.size() - 1], p[i]) <= 0)
            convex.pop_back();

        convex.push_back(p[i]);
    }
    return convex;
}

double RotatingCalipers(const vector<Pos>& convex)
{
    const int n = convex.size();

    ll maxDist = 0;
    for (int i = 0, j = 1; i < n; ++i)
    {
        const int in = (i + 1) % n;
        while (true)
        {
            const int jn = (j + 1) % n;
            const Pos v1 = {convex[in].X - convex[i].X, convex[in].Y - convex[i].Y};
            const Pos v2 = {convex[jn].X - convex[j].X, convex[jn].Y - convex[j].Y};

            if (CCW({0, 0}, v1, v2) > 0)
                j = jn;
            else
                break;
        }
        maxDist = max(maxDist, GetDistSquare(convex[i], convex[j]));
    }
    return sqrt(maxDist);
}

int main()
{
    fastio;
    cout.precision(7);
    cout << fixed;

    int n;
    cin >> n;

    vector<Pos> p(n);
    for (auto& [x, y] : p) cin >> x >> y;

    cout << RotatingCalipers(MakeConvex(p));
}
