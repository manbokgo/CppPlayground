// URL: https://www.acmicpc.net/problem/14003
// Algo: DP (LIS + 복원)

// Start:	240705 06 12
// Read:	0 1
// Think:	0 1
// Code:	0 5
// Total:	0 7

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
    vector<int> indices(n);
    vector<int> dp;
    dp.reserve(n);

    cin >> arr[0];
    dp.pb(arr[0]);
    indices[0] = 1;

    for (int i = 1; i < n; ++i)
    {
        cin >> arr[i];
        if (arr[i] > dp.back())
        {
            dp.pb(arr[i]);
            indices[i] = dp.size();
        }
        else
        {
            const int idx = lower_bound(all(dp), arr[i]) - dp.begin();
            dp[idx] = arr[i];
            indices[i] = idx + 1;
        }
    }

    cout << dp.size() << '\n';

    vector<int> answer(dp.size());
    int fIdx = dp.size();
    for (int i = n - 1; i >= 0; --i)
    {
        if (indices[i] == fIdx)
        {
            answer[fIdx - 1] = arr[i];
            --fIdx;
        }
    }

    for (const int num : answer) cout << num << ' ';
}
