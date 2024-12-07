// URL: https://www.acmicpc.net/problem/17371
// Algo: 기하학, 그리디

// Start:	241207 18 48
// Read:	0 2
// Think:	0 34
// Code:	0 12
// Total:   0 48

// 논리적으로 생각해야 간단하게 풀 수 있는 문제. 정답인 점 P에서 가장 가까운 점을 A, 가장 먼 점을 B라고 할 때
// PA + PB 는 어떤 임의의 점 Q에 대해 QA + QB 보다 작거나 같을 것이다.   PA+PB <= QA+QB
// 이는 정답 P가 선분 AB 위에 있어야 한다는 것을 의미하며, 정답 P를 A라고 가정해도 무방하다.  (삼각부등식에 따라 AA+AB <= PA+PB)

// 따라서 정답은 가장 먼 거리가 최소인 점이 될 수 있다.

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) x.begin(), x.end()
#define pb push_back

using pii = pair<int, int>;
constexpr int INF = 0x3f3f3f3f;

int main()
{
    fastio;

    int n;
    cin >> n;

    vector<pii> pos(n);
    for (auto& [x, y] : pos) cin >> x >> y;

    int mn = INF;
    pii answer = {};
    for (const auto [x1, y1] : pos)
    {
        int mx = 0;
        for (const auto [x2, y2] : pos)
        {
            const int distSquare = (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2);
            mx = max(mx, distSquare);
        }

        if (mn > mx)
        {
            mn = mx;
            answer = {x1, y1};
        }
    }

    cout << answer.first << ' ' << answer.second;
}
