// URL: https://www.acmicpc.net/problem/1715
// Algo: 그리디

// Start:	240604 08 02
// Read:	0 1
// Think:	0 2
// Code:	0 4
// Total:	0 7

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) x.begin(), x.end()
#define pb push_back

int main()
{
    fastio;

    priority_queue<int, vector<int>, greater<>> pq;

    int n;
    cin >> n;
    for (int i = 0; i < n; ++i)
    {
        int num;
        cin >> num;
        pq.push(num);
    }

    int answer = 0;
    while (pq.size() >= 2)
    {
        int num1 = pq.top();
        pq.pop();
        int num2 = pq.top();
        pq.pop();

        answer += num1 + num2;
        pq.push(num1 + num2);
    }

    cout << answer;
}
