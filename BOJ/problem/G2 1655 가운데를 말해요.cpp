// URL: https://www.acmicpc.net/problem/1655
// Algo: 우선순위 큐

// Start:	241114 07 46
// Read:	0 1
// Think:	0 1
// Code:	0 10
// Total:	0 12

// G4 7662 이중 우선순위 큐처럼 우선순위 큐를 2개 사용하여 중간값을 찾는다.
// 처음엔 pqMax의 크기를 절반 크기로 유지하여 중간값을 찾도록 풀었다. 24ms
// 다른 사람 코드 보니 그냥 pqMax와 pqMin의 top을 비교하여 스왑하도록 하는게 충분히 빠르고 깔끔한 듯. 28ms

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) x.begin(), x.end()
#define pb push_back

int main()
{
    fastio;

    int n;
    cin >> n;

    priority_queue<int> pqMax;
    priority_queue<int, vector<int>, greater<>> pqMin;

    while (n--)
    {
        int num;
        cin >> num;

        if (pqMax.size() == pqMin.size()) pqMax.push(num);
        else pqMin.push(num);

        while (!pqMin.empty() && !pqMax.empty() &&
            pqMax.top() > pqMin.top())
        {
            int a = pqMax.top();
            pqMax.pop();

            int b = pqMin.top();
            pqMin.pop();

            pqMax.push(b);
            pqMin.push(a);
        }

        cout << pqMax.top() << '\n';
    }

    // pq 크기를 기준으로 스왑
    // for (int i = 0; i < n; ++i)
    // {
    //     int num;
    //     cin >> num;
    //
    //     if (pqMax.empty() || pqMax.top() >= num) pqMax.push(num);
    //     else pqMin.push(num);
    //
    //     while (pqMax.size() < i / 2 + 1)
    //     {
    //         pqMax.push(pqMin.top());
    //         pqMin.pop();
    //     }
    //
    //     while (pqMax.size() > i / 2 + 1)
    //     {
    //         pqMin.push(pqMax.top());
    //         pqMax.pop();
    //     }
    //
    //     cout << pqMax.top() << '\n';
    // }
}
