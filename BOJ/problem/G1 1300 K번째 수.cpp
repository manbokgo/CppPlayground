// URL: https://www.acmicpc.net/problem/1300
// Algo: 매개 변수 탐색

// Start:	250125 13 01
// Read:	0 2
// Think:	0 10
// Code:	0 18
// Total:	0 30

// mid: 1 2 3 4 5 6 7 8 9
// cnt: 1 3 5 6 6 8 8 8 9

// mid의 최솟값을 구해야 한다. FFFFTTTT

// cnt는 mid 이하인 수의 개수.
// mid가 k번째 수가 되기 위해서는 최소한 cnt가 k 이상이어야 한다. (T)
// 만약 k 미만이라면 절대 mid는 k번째 수가 될 수 없다. (F)

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) x.begin(), x.end()
#define pb push_back

int main()
{
    fastio;

    int n, k;
    cin >> n >> k;

    int lo = 1;
    int hi = k; // 원래는 n * n. k번째 수는 항상 k 이하이므로 k로 초기화 가능.
    while (lo < hi)
    {
        const int mid = (lo + hi) / 2;

        int cnt = 0;
        for (int i = 1; i <= n; ++i)
            cnt += min(mid / i, n);

        if (cnt >= k) hi = mid;
        else lo = mid + 1;
    }
    cout << lo;
}
