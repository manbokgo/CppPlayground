// URL: https://www.acmicpc.net/problem/2467
// Algo: 투 포인터 or 이분 탐색

// Start:	240528 17 33
// Read:	0 1
// Think:	0 1
// Code:	0 19    INF 범위, lower_bound 인덱스 실수로 헤맴
// Total:	0 21

// 투 포인터로 풀린다는건 알았는데, 왠지 이분 탐색으로 풀고 싶어서 lower_bound 잘못 썼다가 오래 헤맴
// arr.begin() + i "+ 1" 을 해야지 자기자신 이후를 탐색하는 거다..
// 또한 10억 10억 테케 때문에 INF 범위를 평소처럼 0x3f3f3f3f (10억)으로 두면 안 되고 int 최대값 21억으로 해놔야 한다

// 투 포인터로 해보니 엄청 간단한 코드로 바로 정답받는거 보니 괜히 했다 싶음

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) x.begin(), x.end()
#define pb push_back

constexpr int INF = INT_MAX;
vector<int> arr;

int main()
{
    fastio;

    int n;
    cin >> n;
    arr.reserve(n);
    for (int i = 0; i < n; ++i)
    {
        int num;
        cin >> num;
        arr.pb(num);
    }

    int mn = INF;
    int a = -1;
    int b = -1;

    // 투 포인터
    /*
    int lo = 0;
    int hi = n-1;
    while (lo < hi)
    {
        int sum = arr[lo] + arr[hi];
        if (mn > abs(sum))
        {
            mn = abs(sum);
            a = arr[lo];
            b = arr[hi];
        }

        if (sum >= 0) --hi;
        else ++lo;
    }
    */

    // 이분 탐색
    for (int i = 0; i < n; ++i)
    {
        const int num = arr[i];
        int idx = lower_bound(arr.begin() + i + 1, arr.end(), -num) - arr.begin();
        if (idx != n && mn > abs(num + arr[idx]))
        {
            mn = abs(num + arr[idx]);
            a = num;
            b = arr[idx];
        }

        --idx;
        if (i < idx && mn > abs(num + arr[idx]))
        {
            mn = abs(num + arr[idx]);
            a = num;
            b = arr[idx];
        }
    }


    cout << a << ' ' << b;
}
