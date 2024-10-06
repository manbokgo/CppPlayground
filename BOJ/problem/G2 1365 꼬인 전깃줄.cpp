// URL: https://www.acmicpc.net/problem/1365
// Algo: DP (LIS)

// Start:	241006 17 14
// Read:	0 1
// Think:	0 1
// Code:	0 2
// Total:	0 4

// P5 2568 전깃줄-2 문제와 거의 같다. 단순히 LIS 길이를 구하여 끊어야 하는 전깃줄 수를 구하는 것까지만 하면 되고,
// 어떤 전깃줄을 끊어야 하는지는 알 필요가 없으니 복원하는 부분(indices)는 필요 없다.

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) x.begin(), x.end()
#define pb push_back

int main()
{
    fastio;

    int n;
    cin >> n;

    vector<int> arr(n);
    for (int i = 0; i < n; ++i)
        cin >> arr[i];

    vector<int> dp;
    dp.reserve(n);

    for (const int num : arr)
    {
        if (dp.empty() || num > dp.back())
        {
            dp.pb(num);
            continue;;
        }

        const int idx = lower_bound(all(dp), num) - dp.begin();
        dp[idx] = num;
    }

    cout << n - dp.size();
}
