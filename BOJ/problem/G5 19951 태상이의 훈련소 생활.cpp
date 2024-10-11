// URL: https://www.acmicpc.net/problem/19951
// Algo: 누적 합

// Start:	241012 06 42
// Read:	0 1
// Think:	0 1
// Code:	0 3
// Total:	0 5

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) x.begin(), x.end()
#define pb push_back

int arr[100'005];
int sum[100'005];

int main()
{
    fastio;

    int n, m;
    cin >> n >> m;

    for (int i = 1; i <= n; ++i)
        cin >> arr[i];

    while (m--)
    {
        int a, b, c;
        cin >> a >> b >> c;
        sum[a] += c;
        sum[b + 1] -= c;
    }

    for (int i = 1; i <= n; ++i)
        sum[i] += sum[i - 1];

    for (int i = 1; i <= n; ++i)
        cout << arr[i] + sum[i] << ' ';
}
