// URL: https://www.acmicpc.net/problem/2696
// Algo: 우선순위 큐

// Start:	240831 18 39
// Read:	0 1
// Think:	0 6
// Code:	0 6
// Total:	0 13

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
        int m;
        cin >> m;

        int mid;
        cin >> mid;

        cout << (m - 1) / 2 + 1 << '\n';
        cout << mid << ' ';

        priority_queue<int, vector<int>, greater<>> pqUp;
        priority_queue<int> pqDown;

        for (int i = 1; i < m; ++i)
        {
            int num;
            cin >> num;

            if (num > mid) pqUp.push(num);
            else pqDown.push(num);

            if (i % 2 == 0)
            {
                if (pqUp.size() > pqDown.size())
                {
                    pqDown.push(mid);
                    mid = pqUp.top();
                    pqUp.pop();
                }
                else if (pqUp.size() < pqDown.size())
                {
                    pqUp.push(mid);
                    mid = pqDown.top();
                    pqDown.pop();
                }

                cout << mid << ' ';
            }
        }

        cout << '\n';
    }
}
