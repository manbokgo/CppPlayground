// URL: https://www.acmicpc.net/problem/7662
// Algo: 우선순위 큐

// Start:	240817 09 00
// Read:	0 2
// Think:	0 2
// Code:	0 22
// Total:	0 26

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
        int k;
        cin >> k;

        priority_queue<int> pq;                          // 최대
        priority_queue<int, vector<int>, greater<>> pq2; // 최소
        unordered_map<int, int> um;                      // 개수 카운팅

        while (k--)
        {
            char c;
            int num;
            cin >> c >> num;

            if (c == 'I')
            {
                ++um[num];
                pq.push(num);
                pq2.push(num);
            }
            else if (c == 'D')
            {
                if (pq.empty() && pq2.empty()) continue;

                if (num == 1)
                {
                    --um[pq.top()];
                    pq.pop();
                }
                else
                {
                    --um[pq2.top()];
                    pq2.pop();
                }

                while (!pq.empty() && um[pq.top()] == 0) pq.pop();
                while (!pq2.empty() && um[pq2.top()] == 0) pq2.pop();
            }
        }

        if (!pq.empty() && !pq2.empty())
            cout << pq.top() << ' ' << pq2.top() << '\n';
        else
            cout << "EMPTY\n";
    }
}
