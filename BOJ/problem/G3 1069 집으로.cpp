// URL: https://www.acmicpc.net/problem/1069
// Algo: 애드 혹, 기하학

// Start:	241106 15 04
// Read:	0 2
// Think:	0 5
// Code:	0 9
// Total:	0 16

// 기하학적으로 원의 중심에서부터 r 거리를 점프한다고 할 떄, 2번 점프하면 2r 범위 내의 어느 지점이든 도달할 수 있다.
// 예제 입력 6번이 힌트다. 직선 거리상 최대한 점프한 것 외에도, +1회 점프한 것까지도 비교해야 한다.

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) x.begin(), x.end()
#define pb push_back

int main()
{
    fastio;

    int x, y, d, t;
    cin >> x >> y >> d >> t;
    cout.precision(9);

    double dist = sqrt(x * x + y * y);
    if (d < t)
    {
        cout << fixed << dist;
        return 0;
    }

    double answer = dist;

    const int jmpCnt = (int)(dist / d);
    dist -= d * jmpCnt;

    if (jmpCnt == 0) answer = min({answer, t + d - dist, t * 2.0});
    else answer = min({answer, t * jmpCnt + dist, t * (jmpCnt + 1.0)});

    cout << fixed << answer;
}
