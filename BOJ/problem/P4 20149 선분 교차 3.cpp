// URL: https://www.acmicpc.net/problem/20149
// Algo: CCW, 선분 교차 판정

// Start:	240823 17 24
// Read:	0 1
// Think:	1 20
// Code:	0 13
// Total:	1 34

// 지식이 늘었다. 수학적인 사고 능력을 더 길러야 한다.

// 행렬식이 0이라는 것은 두 직선이 평행하다는 것을 의미한다.
// https://blog.naver.com/junhyuk7272/50130316177

// 교점은 두 직선의 방정식을 연립하여 풀 수도 있고,
// https://cocoon1787.tistory.com/489

// 외적의 절대값(평행사변형 크기)에 비례하여 l2를 나눈다는 점 이해하고 쉽게 풀었다.
// https://mona04.github.io/posts/algorithm/boj-platinum/BOJ-20149)-%EC%84%A0%EB%B6%84%EA%B5%90%EC%B0%A83/

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

    if (ret1 > 0 || ret2 > 0)
    {
        cout << 0;
        return false;
    }
    if (ret1 < 0 || ret2 < 0)
    {
        cout << 1 << '\n';

        // 외적 a, b의 절대값의 비율로 l2를 나누기 때문에 lerp 할 수 있다
        double alpha = (double)abs(a) / ((double)abs(a) + (double)abs(b));

        cout.precision(16);
        cout << l2.p1.X * (1.0 - alpha) + l2.p2.X * alpha << ' ';
        cout << l2.p1.Y * (1.0 - alpha) + l2.p2.Y * alpha;

        return true;
    }

    // 일직선상 혹은 끝점 겹침 ret1 == 0 && ret2 == 0
    if (l1.p1 > l1.p2) swap(l1.p1, l1.p2);
    if (l2.p1 > l2.p2) swap(l2.p1, l2.p2);

    if (l1.p2 < l2.p1 || l1.p1 > l2.p2) // 서로 떨어져있다
    {
        cout << 0;
        return false;
    }

    cout << 1 << '\n';

    const ll determinant = (l1.p1.X - l1.p2.X) * (l2.p1.Y - l2.p2.Y) - (l1.p1.Y - l1.p2.Y) * (l2.p1.X - l2.p2.X);
    if (determinant == 0) // 평행
    {
        if (l1.p1 == l2.p2) cout << l1.p1.X << ' ' << l1.p1.Y;
        else if (l1.p2 == l2.p1) cout << l1.p2.X << ' ' << l1.p2.Y;
        // else 완전히 겹침
    }
    else
    {
        if (l1.p1 == l2.p1 || l1.p1 == l2.p2) cout << l1.p1.X << ' ' << l1.p1.Y;
        else if (l1.p2 == l2.p1 || l1.p2 == l2.p2) cout << l1.p2.X << ' ' << l1.p2.Y;
    }

    return true;
}

int main()
{
    fastio;

    Line l1, l2;
    cin >> l1.p1.X >> l1.p1.Y >> l1.p2.X >> l1.p2.Y
        >> l2.p1.X >> l2.p1.Y >> l2.p2.X >> l2.p2.Y;

    LineCrossed(l1, l2);
}
