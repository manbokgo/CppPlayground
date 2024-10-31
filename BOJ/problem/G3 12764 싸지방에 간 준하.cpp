// URL: https://www.acmicpc.net/problem/12764
// Algo: 우선순위 큐, 시뮬레이션

// Start:	241031 15 31
// Read:	0 1
// Think:	0 5
// Code:	0 17
// Total:	0 23

// 비어있는 자리 중 가장 앞번호에 앉는다는 조건이 핵심이다.
// 특정 시점에서 비어있는 자리들을 담고 있는 pq가 하나 더 필요했던 문제.

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) x.begin(), x.end()
#define pb push_back

using pii = pair<int, int>;

int main()
{
    fastio;

    int n;
    cin >> n;

    vector<pii> times(n);
    for (auto& [st, en] : times)
        cin >> st >> en;
    sort(all(times));

    priority_queue<pii, vector<pii>, greater<>> pq;
    priority_queue<int, vector<int>, greater<>> availSeat;
    vector<int> usages;

    for (const auto [st, en] : times)
    {
        while (!pq.empty())
        {
            const auto [cEn, cIdx] = pq.top();
            if (st < cEn) break;
            availSeat.push(cIdx);
            pq.pop();
        }

        if (availSeat.empty())
        {
            pq.push({en, (int)usages.size()});
            usages.pb(1);
            continue;
        }

        const int sIdx = availSeat.top();
        availSeat.pop();

        pq.push({en, sIdx});
        ++usages[sIdx];
    }

    cout << usages.size() << '\n';
    for (const int num : usages) cout << num << ' ';
}
