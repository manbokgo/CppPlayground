// URL: https://www.acmicpc.net/problem/15654
// Algo: 백트래킹

// Start:	250109 06 21
// Read:	0 1
// Think:	0 2
// Code:	0 6
// Total:	0 9

// next_permutation으로 하려면 2중으로 해야해서 번거로워진다.
// 정석적으로 백트래킹하는게 깔끔함.

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) x.begin(), x.end()
#define pb push_back

int n, m;
int org[8];
int arr[8];
bool used[8];

void Solve(int idx)
{
    if (idx == m)
    {
        for (int i = 0; i < m; ++i)
            cout << arr[i] << ' ';
        cout << '\n';
        return;
    }

    for (int i = 0; i < n; ++i)
    {
        if (used[i]) continue;
        used[i] = true;
        arr[idx] = org[i];
        Solve(idx + 1);
        used[i] = false;
    }
}

int main()
{
    fastio;

    cin >> n >> m;
    for (int i = 0; i < n; ++i)
        cin >> org[i];

    sort(org, org + n);
    Solve(0);
}
