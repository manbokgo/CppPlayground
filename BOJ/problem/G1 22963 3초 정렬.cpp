// URL: https://www.acmicpc.net/problem/22963
// Algo: DP (LIS + 복구)

// Start:	240702 09 46
// Read:	0 2
// Think:	0 3
// Code:	0 46
// Total:	0 51

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
    for (int& num : arr)
        cin >> num;

    vector<int> indices(n, -1);
    vector<int> dp;
    dp.reserve(n);

    for (int i = 0; i < n; ++i)
    {
        int idx = upper_bound(dp.begin(), dp.end(), arr[i]) - dp.begin();
        if (idx == dp.size())
        {
            dp.pb(arr[i]);
            indices[i] = dp.size() - 1;
            continue;
        }
        dp[idx] = arr[i];
        indices[i] = idx;
    }

    if (n - dp.size() > 3)
    {
        cout << "NO";
        return 0;
    }

    cout << "YES\n" << n - dp.size() << '\n';

    int fIdx = dp.size() - 1;
    int lastNum = 1e9;
    for (int i = n - 1; i >= 0; --i)
    {
        if (indices[i] == fIdx)
        {
            lastNum = arr[i];
            --fIdx;
        }
        else
        {
            cout << i + 1 << ' ' << lastNum << '\n';
        }
    }
}
