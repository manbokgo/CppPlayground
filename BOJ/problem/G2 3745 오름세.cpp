// URL: https://www.acmicpc.net/problem/3745
// Algo: DP (LIS)

// Start:	240317 04 44
// Read:	0 0
// Think:	0 0
// Code:	0 5
// Total:	0 5

#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define Y first
#define X second
#define all(x) x.begin(), x.end()
#define SortVec(x) sort(all(x))
#define CompressVec(x) x.erase(unique(all(x)), x.end())
#define ExistInVec(x, value) find(all(x), value) != x.end()

using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using tiii = tuple<int, int, int>;
using tlll = tuple<ll, ll, ll>;

constexpr int INF = 0x3f3f3f3f;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    while (cin >> n)
    {
        vector<int> dp(n, INF);
        int answer = 1;
        for (int i = 0; i < n; ++i)
        {
            int price;
            cin >> price;
            int idx = lower_bound(all(dp), price) - dp.begin();
            answer = max(answer, idx + 1);
            dp[idx] = price;
        }

        cout << answer << '\n';
    }
}
