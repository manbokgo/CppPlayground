// URL: https://www.acmicpc.net/problem/13904
// Algo: 그리디, 우선순위 큐

// Start:	240905 16 20
// Read:	0 1
// Think:	0 0
// Code:	0 5
// Total:	0 6

// G2 1781 컵라면과 동일한 문제다.

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) x.begin(), x.end()
#define pb push_back

using pii = pair<int, int>;

pii arr[1'000];

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

    sort(arr, arr + n, greater<>());
    priority_queue<int> pq;
    
    int answer = 0;
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
            answer += pq.top();
            pq.pop();
        }
    }
    cout << answer;
}
