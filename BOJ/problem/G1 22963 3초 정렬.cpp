// URL: https://www.acmicpc.net/problem/22963
// Algo: DP (LIS + 복원)

// Start:	240702 09 46
// Read:	0 2
// Think:	0 3
// Code:	0 46
// Total:	0 51

// 일반적인 LIS와 달리 이 문제에선 8 8 8 도 유효한 오름차순 수열이기 때문에
// lower_bound가 아니라 upper_bound를 써야 한다

// LIS의 길이가 n과 3 넘게 차이난다면 무조건 불가능함
// LIS를 복원하는 과정에서 스킵되는 것들이 수정되는 것들이다

// + https://blog.naver.com/jinhan814/222900789618
// DP 풀이 꽤 재밌다. 시간은 비슷한데 메모리는 3배 씀

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

// DP 풀이
// https://blog.naver.com/jinhan814/222900789618
/*
constexpr int INF = 0x3f3f3f3f;
int main()
{
    fastio;

    int n;
    cin >> n;
    vector<int> arr(n + 1);
    for (int i = 1; i <= n; ++i)
        cin >> arr[i];

    vector<vector<int>> dp(n + 1, vector<int>(4));
    dp[1][0] = arr[1];
    dp[1][1] = dp[1][2] = dp[1][3] = 1;

    for (int i = 2; i <= n; ++i)
    {
        dp[i][0] = dp[i - 1][0] <= arr[i] ? arr[i] : INF;
        for (int j = 1; j <= 3; ++j)
        {
            dp[i][j] = dp[i - 1][j - 1];
            if (dp[i - 1][j] <= arr[i])
                dp[i][j] = min(dp[i][j], arr[i]);
        }
    }

    int mn = INF;
    int idx = 0;
    for (int i = 0; i < 4; i++)
    {
        if (mn > dp[n][i])
        {
            mn = dp[n][i];
            idx = i;
        }
    }

    if (mn == INF)
    {
        cout << "NO";
        return 0;
    }

    cout << "YES" << '\n' << idx << '\n';

    for (int i = n, j = idx; i >= 1 && j; --i)
    {
        if (dp[i - 1][j] > arr[i] || dp[i - 1][j - 1] < arr[i])
            cout << i << ' ' << dp[i][j--] << '\n';
    }
}
*/

