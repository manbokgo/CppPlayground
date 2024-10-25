// URL: https://www.acmicpc.net/problem/14002
// Algo: DP (LIS + 복원)

// Start:	241026 08 37
// Read:	0 1
// Think:	0 0
// Code:	0 0
// Total:	0 1

// LIS 5 문제 복붙

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) x.begin(), x.end()
#define pb push_back

constexpr int INF = 0x3f3f3f3f;

int main()
{
    fastio;

    int n;
    cin >> n;

    vector<int> seq(n);
    vector<int> indices(n);
    vector<int> dp(n, INF);

    for (int i = 0; i < n; ++i)
    {
        cin >> seq[i];
        int idx = lower_bound(all(dp), seq[i]) - dp.begin();
        dp[idx] = seq[i];
        indices[i] = idx + 1;
    }
    const int LIS = lower_bound(all(dp), INF) - dp.begin();

    cout << LIS << '\n';

    vector<int> answer(LIS);
    int fIdx = LIS;
    for (int i = n - 1; i >= 0; --i)
    {
        if (indices[i] == fIdx)
        {
            answer[fIdx - 1] = seq[i];
            --fIdx;
        }
    }

    for (const int num : answer) cout << num << ' ';
}
