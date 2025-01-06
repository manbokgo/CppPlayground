// URL: https://www.acmicpc.net/problem/15650
// Algo: 백트래킹

// Start:	250106 17 53
// Read:	0 1
// Think:	0 2
// Code:	0 4
// Total:	0 7

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) x.begin(), x.end()
#define pb push_back

int n, m;
int arr[8];

void Solve(int idx)
{
    if (idx == m)
    {
        for (int i = 0; i < m; ++i)
        {
            cout << arr[i] << ' ';
        }
        cout << '\n';
        return;
    }

    int st = 1;
    if (idx != 0) st = arr[idx - 1] + 1;

    for (int i = st; i <= n; ++i)
    {
        arr[idx] = i;
        Solve(idx + 1);
    }
}

int main()
{
    fastio;

    cin >> n >> m;

    // 백트래킹 풀이
    // Solve(0);
    // return 0;

    vector<bool> comb(n);
    for (int i = 0; i < m; ++i) comb[i] = true;

    do
    {
        for (int i = 0; i < n; ++i)
            if (comb[i]) cout << i + 1 << ' ';

        cout << '\n';
    }
    while (prev_permutation(all(comb)));
}
