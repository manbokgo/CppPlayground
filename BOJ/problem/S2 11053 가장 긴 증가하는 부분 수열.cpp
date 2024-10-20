// URL: https://www.acmicpc.net/problem/11053
// Algo: DP (LIS 기본)

// Start:	240220 00 19
// Read:	0 0
// Think:	0 2
// Code:	0 10
// Total:	0 12

#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define X first
#define Y second
#define all(x) x.begin(), x.end()
#define sortVec(x) sort(all(x))
#define compress(x) x.erase(unique(all(x)), x.end())
#define existInVec(x, value) find(all(x), value) != x.end()

using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using tiii = tuple<int, int, int>;

constexpr ll MOD = 1000000007;
constexpr int INF = 0x3f3f3f3f;
constexpr ll LLINF = 1e18;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    // 복원이 필요치 않다면 seq 배열은 굳이 필요없다
    vector<int> seq(n);
    vector<int> dp(n, INF);

    for (int i = 0; i < n; ++i)
    {
        cin >> seq[i];
        int idx = lower_bound(all(dp), seq[i]) - dp.begin();
        dp[idx] = seq[i];
    }
    const int LIS = lower_bound(all(dp), INF) - dp.begin();

    cout << LIS;


    // dp reserve 방식. 약간 더 빠르나 if 분기 때문에 코드가 깔끔하지 않음
    /*
    vector<int> dp;
    dp.reserve(n);

    for (int i = 0; i < n; ++i)
    {
        cin >> seq[i];
        if (dp.empty() || seq[i] > dp.back())
        {
            dp.pb(seq[i]);
        }
        else
        {
            const int idx = lower_bound(all(dp), seq[i]) - dp.begin();
            dp[idx] = seq[i];
        }
    }

    cout << dp.size();
    */

}
