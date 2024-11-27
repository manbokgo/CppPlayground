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

vector<Pos> p;
ll DistSquare(Pos p1, Pos p2) { return (p2.X - p1.X) * (p2.X - p1.X) + (p2.Y - p1.Y) * (p2.Y - p1.Y); }

bool GrahamCmp(const Pos& a, const Pos& b)
{
    const ll c = CCW(p[0], a, b);
    if (c == 0) return DistSquare(p[0], a) < DistSquare(p[0], b);
    return c > 0;
}

int main()
{
    fastio;

    int n;
    cin >> n;

    p.resize(n);
    for (auto& [x, y] : p) cin >> x >> y;

    sort(all(p));
    sort(p.begin() + 1, p.end(), GrahamCmp);

    stack<int> S;
    S.push(0);
    S.push(1);

    for (int i = 2; i < n; ++i)
    {
        while (S.size() >= 2)
        {
            const int top1 = S.top();
            S.pop();
            const int top2 = S.top();

            if (CCW(p[top2], p[top1], p[i]) > 0)
            {
                S.push(top1);
                break;
            }
        }
        S.push(i);
    }

    cout << S.size();
}
