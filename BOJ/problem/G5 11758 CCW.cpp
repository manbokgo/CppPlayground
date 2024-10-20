// URL: https://www.acmicpc.net/problem/11758
// Algo: CCW 기본

// Start:	241020 10 33
// Read:	0 1
// Think:	0 1
// Code:	0 1
// Total:	0 3

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

int main()
{
    fastio;

    Pos p1, p2, p3;
    cin >> p1.X >> p1.Y >> p2.X >> p2.Y >> p3.X >> p3.Y;

    cout << Normalize(CCW(p1, p2, p3));
}
