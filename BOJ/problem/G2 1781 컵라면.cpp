// URL: https://www.acmicpc.net/problem/1781
// Algo: 그리디, 우선순위 큐

// Start:	240613 11 29
// Read:	0 1
// Think:	0 16
// Code:	0 12
// Total:	0 29

// G2 1202 보석 도둑과 비슷하다. 보석이 숙제로, 가방이 날짜로.
// day일에 풀 수 있는 문제 후보는 데드라인이 day일 이상인 문제들임을 이용한다.
// day를 역순으로 순회하며 데드라인이 day 이상인 모든 값을 우선순위 큐에 넣어 최대값을 하나씩 뽑는다.


#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) x.begin(), x.end()
#define pb push_back

using pii = pair<int, int>;
pii arr[200'001];

int main()
{
    fastio;

    int n;
    cin >> n;
    for (int i = 0; i < n; ++i)
    {
        auto& [dead, num] = arr[i];
        cin >> dead >> num;
    }

    // 최댓값 뽑기 68ms
    /*
     *sort(arr, arr + n, greater<>());
    priority_queue<int> pq;
    
    int ans = 0;
    int idx = 0;
    for (int time = n; time > 0; --time)
    {
        for (; idx < n; ++idx)
        {
            const auto [dead, num] = arr[idx];
            if (dead < time) break;
            pq.push(num);
        }
    
        if (!pq.empty())
        {
            ans += pq.top();
            pq.pop();
        }
    }
    */

    // 최솟값 대체하기 56ms
    sort(arr, arr + n);
    priority_queue<int, vector<int>, greater<>> pq;

    int ans = 0;
    for (int i = 0; i < n; ++i)
    {
        const auto [dead, num] = arr[i];
        if (pq.size() < dead)
        {
            ans += num;
            pq.push(num);
            continue;
        }

        if (!pq.empty())
        {
            int lowest = pq.top();
            if (num > lowest)
            {
                pq.pop();
                ans -= lowest;
                ans += num;
                pq.push(num);
            }
        }
    }

    cout << ans;
}
