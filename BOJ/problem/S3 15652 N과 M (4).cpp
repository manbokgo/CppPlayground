// URL: https://www.acmicpc.net/problem/15652
// Algo: 백트래킹

// Start:	250107 19 23
// Read:	0 1
// Think:	0 2
// Code:	0 4
// Total:   0 7

// 같은 수를 여러 번 쓸 수 있는 상황에서는 next_permutation을 사용하기가 어렵다.

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
            cout << arr[i] << ' ';
        cout << '\n';
        return;
    }

    int st = 1;
    if (idx != 0) st = arr[idx - 1];
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
    Solve(0);
}
