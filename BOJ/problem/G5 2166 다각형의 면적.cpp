// URL: https://www.acmicpc.net/problem/2166
// Algo: CCW

// Start:	240726 05 35
// Read:	0 2
// Think:	0 16
// Code:	0 7
// Total:   0 25

// 신발끈 공식(CCW)은 의미적으로 2차원에서의 외적(Cross)과 같으며
// 결과값의 크기는 세 점으로 이루어진 평행사변형의 넓이다.
// 부호는 오른손 법칙에 따라(다렉처럼 왼손 좌표계가 아니라 아니라 순수 수학에서 쓰이는 공식으로 하므로 오른손 좌표계임)
// 반시계 방향이면 양수, 시계 방향이면 음수다.

// Convex 볼록한 다각형이면 당연히 다 더하면 되고, Concave 오목한 다각형이여도 똑같이 하면 되는데
// 오목한 부분의 넓이만큼이 음수로 결과값이 나오기 때문에, 다 더하면 그 부분이 알아서 빼지기 때문임

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) x.begin(), x.end()
#define pb push_back

double CCW(double x1, double y1, double x2, double y2, double x3, double y3)
{
    // return (x2 - x1) * (y3 - y1) - (x3 - x1) * (y2 - y1);
    double ret = x1 * y2 + x2 * y3 + x3 * y1;
    ret -= (y1 * x2 + y2 * x3 + y3 * x1);
    return ret;
}

int main()
{
    fastio;
    int n;
    cin >> n;

    int orgX, orgY;
    cin >> orgX >> orgY;

    int prvX, prvY;
    cin >> prvX >> prvY;

    double answer = 0.0;
    for (int i = 2; i < n; ++i)
    {
        int curX, curY;
        cin >> curX >> curY;
        answer += CCW(orgX, orgY, prvX, prvY, curX, curY) / 2.0;

        prvX = curX;
        prvY = curY;
    }

    cout.precision(1);
    cout << fixed << abs(answer);
}
