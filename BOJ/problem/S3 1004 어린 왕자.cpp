// URL: https://www.acmicpc.net/problem/1004
// Algo: 기하학

// Start:	241202 15 50
// Read:	0 2
// Think:	0 7
// Code:	0 4
// Total:	0 13

// 행성계의 경계가 맞닿거나 서로 교차하는 경우는 없는 조건.
// 어떤 행성계를 기준으로, 시작점이 포함되어 있고 도착점이 포함되어 있지 않다면 이 행성계는 탈출해야 하고
// 시작점이 포함되어 있지 않고 도착점이 포함되어 있다면 이 행성계는 진입해야 한다.

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) x.begin(), x.end()
#define pb push_back

int main()
{
    fastio;

    int T;
    cin >> T;

    while (T--)
    {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;

        int n;
        cin >> n;

        int answer = 0;
        while (n--)
        {
            int cx, cy, r;
            cin >> cx >> cy >> r;

            const bool includeStart = (cx - x1) * (cx - x1) + (cy - y1) * (cy - y1) <= r * r;
            const bool includeEnd = (cx - x2) * (cx - x2) + (cy - y2) * (cy - y2) <= r * r;

            // if (includeStart ^ includeEnd) ++answer;

            if (!includeStart && includeEnd) ++answer;
            if (includeStart && !includeEnd) ++answer;
        }
        cout << answer << "\n";
    }
}
