// URL: https://www.acmicpc.net/problem/11054
// Algo: DP (LIS+LDS 응용)

// Start:	240619 14 03
// Read:	0 3
// Think:	0 17
// Code:	0 4
// Total:	0 24

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) x.begin(), x.end()
#define pb push_back

constexpr int INF = 0x3f3f3f3f;

int arr[1000];
int dp[1000];
int front[1000];
int back[1000];

int main()
{
    fastio;
    memset(dp, 0x3f, sizeof(dp));

    int n;
    cin >> n;
    for (int i = 0; i < n; ++i)
    {
        cin >> arr[i];
        int idx = lower_bound(begin(dp), end(dp), arr[i]) - begin(dp);
        front[i] = idx + 1;
        dp[idx] = arr[i];
    }

    memset(dp, 0x3f, sizeof(dp));
    for (int i = n - 1; i >= 0; --i)
    {
        int idx = lower_bound(begin(dp), end(dp), arr[i]) - begin(dp);
        back[i] = idx + 1;
        dp[idx] = arr[i];
    }

    int answer = 0;
    for (int i = 0; i < n; ++i)
        answer = max(answer, front[i] + back[i] - 1);
    cout << answer;
}
