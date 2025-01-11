// URL: https://www.acmicpc.net/problem/15666
// Algo: 백트래킹

// Start:	250111 23 59
// Read:	0 1
// Think:	0 2
// Code:	0 1
// Total:	0 4

// S2 15663 N과 M (9)과 S3 15652 N과 M (4)를 섞은 문제.
// 중복 수열이 나오지 않도록 이전 확정 수열의 마지막 항에 다른 숫자를 넣는 건 동일하다.
// 중복 사용이 가능한만큼 used 배열은 빼고, 비내림차 순을 유지하도록 후보 시작 인덱스를 함수 인자로 넘겨준다.

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) x.begin(), x.end()
#define pb push_back

int n, m;
int org[8];
int arr[8];

void Solve(int idx, int st)
{
    if (idx == m)
    {
        for (int i = 0; i < m; ++i)
            cout << arr[i] << ' ';
        cout << '\n';
        return;
    }

    int lastUsed = -1;
    for (int i = st; i < n; ++i)
    {
        if (lastUsed == org[i]) continue; // 이전 수열의 마지막 항과 동일한지 확인

        arr[idx] = org[i];
        lastUsed = org[i];
        Solve(idx + 1, i);
    }
}

int main()
{
    fastio;

    cin >> n >> m;
    for (int i = 0; i < n; ++i)
        cin >> org[i];

    sort(org, org + n);
    Solve(0, 0);
}
