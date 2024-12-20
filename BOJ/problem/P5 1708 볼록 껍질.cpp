// URL: https://www.acmicpc.net/problem/1708
// Algo: 볼록 껍질 기본

// Start:	241127 10 41
// Read:	0 1
// Think:	0 3
// Code:	0 16
// Total:   0 20

// https://david0506.tistory.com/62
// https://blog.naver.com/kks227/220857597424
// 그라함 스캔

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

vector<Pos> MakeConvex(vector<Pos> p)
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

int main()
{
    fastio;

    int n;
    cin >> n;

    vector<Pos> p(n);
    for (auto& [x, y] : p) cin >> x >> y;

    cout << MakeConvex(p).size();
}
