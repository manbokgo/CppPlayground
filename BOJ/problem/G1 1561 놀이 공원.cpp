// URL: https://www.acmicpc.net/problem/1561
// Algo: 매개 변수 탐색

// Start:	250126 16 00
// Read:	0 1
// Think:	0 4
// Code:	0 16
// Total:	0 21

// G5 3079 입국심사 문제처럼 매개 변수 탐색으로 모든 아이가 다 탑승하게 되는 최종 시간을 구한다.
// 최종 시간 - 1 시점까지 탑승한 아이들의 수를 구하고, 최종 시간 시점에 탑승할 수 있는 기구들을 쭉 순회하며
// 마지막 아이가 탑승하는 기구 번호를 알아낸다.

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) x.begin(), x.end()
#define pb push_back

using ll = long long;

int times[10'001];

int main()
{
    fastio;

    int n, m;
    cin >> n >> m;

    if (n <= m)
    {
        cout << n;
        return 0;
    }

    for (int i = 1; i <= m; ++i)
        cin >> times[i];

    ll lo = 0;
    ll hi = 6e10;

    while (lo < hi)
    {
        const ll mid = (lo + hi) / 2;

        ll cnt = m;
        for (int i = 1; i <= m; ++i)
            cnt += mid / times[i];

        if (cnt >= n) hi = mid;
        else lo = mid + 1;
    }

    int dealt = m;
    for (int i = 1; i <= m; ++i)
        dealt += (lo - 1) / times[i];

    for (int i = 1; i <= m; ++i)
    {
        if (lo % times[i] == 0)
            ++dealt;

        if (dealt == n)
        {
            cout << i;
            return 0;
        }
    }
}
