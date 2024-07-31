// URL: https://www.acmicpc.net/problem/2613
// Algo: 이분 탐색, 매개변수 탐색

// Start:	240731 19 16
// Read:	0 1
// Think:	0 3
// Code:	0 42
// Total:	0 46

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) x.begin(), x.end()
#define pb push_back

constexpr int INF = 0x3f3f3f3f;
int arr[300];

int main()
{
    fastio;

    int n, m;
    cin >> n >> m;

    int mx = -1;
    for (int i = 0; i < n; ++i)
    {
        cin >> arr[i];
        mx = max(mx, arr[i]);
    }

    int lo = mx; // 이보다 작으면 1개짜리도 구간 못 만듦
    int hi = 100 * n;
    while (lo < hi)
    {
        // 어떤 구간의 최대값
        const int mid = (lo + hi) / 2;

        int tmp = 0;
        int cnt = 0;
        for (int i = 0; i < n; ++i)
        {
            tmp += arr[i];
            if (tmp > mid)
            {
                tmp = arr[i];
                ++cnt;
            }
        }
        ++cnt; // 마지막 구간

        if (cnt <= m) hi = mid;
        else lo = mid + 1;
    }

    cout << lo << '\n';

    int tmp = 0;
    int cnt = 0;
    int grpCnt = 0;
    for (int i = 0; i < n; ++i)
    {
        // 남은 배열과, 남은 그룹 개수 + 현재 진행중인 구간이 같다면
        // 현재 진행 중이었던 구간을 그룹 하나로 마무리하고
        // 남은 나머지를 1개짜리 그룹으로 만들어 그룹 개수를 채운다.
        if (n - i == m - grpCnt - 1)
        {
            ++grpCnt;
            cout << cnt << ' ';

            while (grpCnt < m)
            {
                ++grpCnt;
                cout << 1 << ' ';
            }
            return 0;
        }

        tmp += arr[i];
        if (tmp > lo)
        {
            ++grpCnt;
            cout << cnt << ' ';
            tmp = arr[i];
            cnt = 0;
        }
        ++cnt;
    }
    cout << cnt << ' ';
}
