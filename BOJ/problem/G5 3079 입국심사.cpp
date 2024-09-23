// URL: https://www.acmicpc.net/problem/3079
// Algo: 이분 탐색, 매개변수 탐색

// Start:	240923 09 38
// Read:	0 1
// Think:	0 1
// Code:	0 20
// Total:	0 22

// LV3 43238 입국심사 문제와 거의 같다.
// cnt가 오버플로된다는 걸 캐치하지 못해서 엄청 헤맴. 아...

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) x.begin(), x.end()
#define pb push_back

using ll = long long;

ll arr[100'000];

int main()
{
    fastio;

    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; ++i)
        cin >> arr[i];

    ll lo = 1;
    ll hi = 1e18;

    while (lo < hi)
    {
        const ll mid = (lo + hi) / 2LL;

        ll cnt = 0;
        for (int i = 0; i < n; ++i)
        {
            cnt += mid / arr[i];
            if (cnt >= m) break; // 오버플로의 원흉
        }

        if (cnt >= m) hi = mid;
        else lo = mid + 1LL;
    }

    cout << lo;
}
