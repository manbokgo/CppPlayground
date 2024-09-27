// URL: https://www.acmicpc.net/problem/2568
// Algo: DP (LIS + 복원)

// Start:	240927 15 40
// Read:	0 1
// Think:	0 1
// Code:	0 19
// Total:	0 21

// P5 14003 LIS 5 문제와 유사하다. 차이점은 복원되지 않는 것들을 출력해야 한다는 것.

// LIS의 길이를 바로 구하기 위해 dp vector의 size()를 보는 방식이라
// arr, indices 등도 일관적이게 vector를 썼다.

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) x.begin(), x.end()
#define pb push_back

using pii = pair<int, int>;

int main()
{
    fastio;

    int n;
    cin >> n;

    vector<pii> arr(n);
    for (int i = 0; i < n; ++i)
    {
        cin >> arr[i].first >> arr[i].second;
    }
    sort(all(arr));

    vector<int> indices(n);
    vector<int> dp;
    dp.reserve(n);

    for (int i = 0; i < n; ++i)
    {
        const auto [a, b] = arr[i];
        if (dp.empty() || b > dp.back())
        {
            dp.pb(b);
            indices[i] = dp.size();
            continue;;
        }

        const int idx = lower_bound(all(dp), b) - dp.begin();
        dp[idx] = b;
        indices[i] = idx + 1;
    }

    cout << n - dp.size() << '\n';

    vector<int> answer;
    answer.reserve(n - dp.size());

    int fIdx = dp.size();
    for (int i = n - 1; i >= 0; --i)
    {
        if (indices[i] == fIdx)
        {
            --fIdx;
            continue;
        }

        answer.pb(arr[i].first);
    }

    for (int i = answer.size() - 1; i >= 0; --i)
        cout << answer[i] << '\n';
}
