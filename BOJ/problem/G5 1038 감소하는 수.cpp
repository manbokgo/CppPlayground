// URL: https://www.acmicpc.net/problem/1038
// Algo: 브루트포스

// Start:	241021 15 14
// Read:	0 1
// Think:	0 9
// Code:	0 2
// Total:	0 12

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) x.begin(), x.end()
#define pb push_back

using ll = long long;

int main()
{
    fastio;

    int n;
    cin >> n;

    queue<ll> q;
    for (int i = 0; i <= 9; ++i)
        q.push(i);

    int cnt = -1;
    while (!q.empty())
    {
        ll num = q.front();
        q.pop();

        ++cnt;
        if (cnt == n)
        {
            cout << num;
            return 0;
        }

        for (int i = 0; i < num % 10; ++i)
        {
            q.push(num * 10 + i);
        }
    }

    cout << -1;
}
