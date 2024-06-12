// URL: https://www.acmicpc.net/problem/13549
// Algo: 0-1 BFS

// Start:	240612 11 06
// Read:	0 1
// Think:	0 2
// Code:	0 17
// Total:	0 20

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) x.begin(), x.end()
#define pb push_back

int visited[100'001];

int main()
{
    fastio;

    memset(visited, 0x3f, sizeof(visited));

    int n, k;
    cin >> n >> k;

    deque<int> dq;
    visited[n] = 0;
    dq.push_front(n);
    int mxLimit = 100'001;

    while (!dq.empty())
    {
        const int num = dq.front();
        dq.pop_front();

        if (num == k)
        {
            cout << visited[num];
            return 0;
        }

        if (num < k && num * 2 < mxLimit && visited[num * 2] > visited[num]) // k보다 작으면 2배
        {
            if (num * 2 > k) mxLimit = num * 2;
            visited[num * 2] = visited[num];
            dq.push_front(num * 2);
        }

        if (num > 0 && visited[num - 1] > visited[num] + 1) // 0보다 크면 -1
        {
            visited[num - 1] = visited[num] + 1;
            dq.push_back(num - 1);
        }

        if (num < k && visited[num + 1] > visited[num] + 1) // k보다 작으면 +1
        {
            visited[num + 1] = visited[num] + 1;
            dq.push_back(num + 1);
        }

    }
}
