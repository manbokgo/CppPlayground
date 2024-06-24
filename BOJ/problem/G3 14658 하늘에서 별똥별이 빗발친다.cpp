// URL: https://www.acmicpc.net/problem/14658
// Algo: 브루트포스

// Start:	240625 06 45
// Read:	0 2
// Think:	0 14
// Code:	0 3
// Total:	0 19

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) x.begin(), x.end()
#define pb push_back

using pii = pair<int, int>;

int main()
{
    fastio;

    int n, m, l, k;
    cin >> n >> m >> l >> k;

    vector<pii> stars(k);
    for (int i = 0; i < k; ++i)
    {
        auto& [y, x] = stars[i];
        cin >> y >> x;
    }

    int ans = 0;
    for (int yIdx = 0; yIdx < k; ++yIdx)
    {
        const int stY = stars[yIdx].first;
        const int enY = stY + l;

        for (int xIdx = 0; xIdx < k; ++xIdx)
        {
            const int stX = stars[xIdx].second;
            const int enX = stX + l;

            int cnt = 0;
            for (int i = 0; i < k; ++i)
            {
                const auto [y, x] = stars[i];
                if (y < stY || y > enY || x < stX || x > enX) continue;
                ++cnt;
            }
            ans = max(ans, cnt);
        }
    }

    cout << k - ans;
}
