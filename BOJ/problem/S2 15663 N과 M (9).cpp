// URL: https://www.acmicpc.net/problem/15663
// Algo: 백트래킹

// Start:	250110 07 12
// Read:	0 1
// Think:	0 3
// Code:	0 5
// Total:	0 10

// 이전에 확정한 수열의 마지막 항 대신 다른 숫자를 넣어야지만 중복 없이 다른 수열이 된다.

// 처음엔 if (arr[idx] == org[i]) continue;  으로 했다가
// 진행 중 더 이상 유효하지 않은 값이 arr에 들어있어 잘못 동작하여 틀림

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

    int lastUsed = -1;
    for (int i = 0; i < n; ++i)
    {
        if (used[i]) continue;
        if (lastUsed == org[i]) continue; // 이전 수열의 마지막 항과 동일한지 확인

        used[i] = true;
        arr[idx] = org[i];
        lastUsed = org[i];
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
