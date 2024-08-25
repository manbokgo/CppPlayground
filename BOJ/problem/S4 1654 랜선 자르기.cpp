// URL: https://www.acmicpc.net/problem/1654
// Algo: 이분 탐색, 매개변수 탐색 기본

// Start:	240825 17 10
// Read:	0 1
// Think:	0 0
// Code:	0 4
// Total:   0 5

// 1. en = mid
// mid의 최솟값을 구해야 한다. FFFFTTTT
// mid가 커질수록 solve(mid)가 커지는데 k 이상(초과)이여야 한다
// mid가 커질수록 solve(mid)가 작아지는데 k 이하(미만)여야 한다

// while (st < en)
// {
//     const int mid = (st + en) / 2;
//     if (T) en = mid;
//     else st = mid + 1;
// }

// 2. st = mid
// mid의 최댓값을 구해야 한다. TTTTFFFF
// mid가 커질수록 solve(mid)가 커지는데 k 이하(미만)여야 한다
// mid가 커질수록 solve(mid)가 작아지는데 k 이상(초과)이여야 한다

// while (st < en)
// {
//     const int mid = (st + en + 1) / 2;
//     if (T) st = mid;
//     else en = mid - 1;
// }

// 이 문제의 경우 2-2에 해당.
// 랜선 길이의 최댓값을 구해야하는데, 랜선 길이가 커질수록 랜선의 개수가 작아짐.
// 그러나 랜선 개수는 n개 이상이여야 함.

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) x.begin(), x.end()
#define pb push_back

using ll = long long;

int k, n;
int arr[10'001];

bool Solve(ll x)
{
    ll cur = 0;
    for (int i = 0; i < k; ++i)
        cur += arr[i] / x;

    return cur >= n;
}

int main()
{
    fastio;
    cin >> k >> n;

    int mx = 0;
    for (int i = 0; i < k; ++i)
    {
        cin >> arr[i];
        mx = max(mx, arr[i]);
    }

    ll st = 1;
    ll en = mx;
    while (st < en)
    {
        const ll mid = (st + en + 1) / 2;
        if (Solve(mid)) st = mid;
        else en = mid - 1;
    }
    cout << st;
}
