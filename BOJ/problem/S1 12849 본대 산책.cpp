// URL: https://www.acmicpc.net/problem/12849
// Algo: DP

// Start:	241004 14 45
// Read:	0 1
// Think:	0 21
// Code:	0 7
// Total:	0 29

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) x.begin(), x.end()
#define pb push_back

using pii = pair<int, int>;
using ll = long long;

constexpr ll MOD = 1000000007;

ll dp[8];
vector<int> adj[8];

int main()
{
    fastio;

    // 간선 추가
    for (auto [a, b] : {
             pii{0, 1},
             pii{0, 2},
             pii{1, 2},
             pii{1, 3},
             pii{2, 3},
             pii{2, 4},
             pii{3, 4},
             pii{3, 5},
             pii{4, 5},
             pii{4, 6},
             pii{5, 7},
             pii{6, 7}
         })
    {
        adj[a].pb(b);
        adj[b].pb(a);
    }

    int m;
    cin >> m;

    dp[0] = 1;
    for (int time = 1; time <= m; ++time)
    {
        ll now[8]{};
        for (int i = 0; i < 8; ++i)
        {
            for (const int nxt : adj[i])
            {
                now[i] += dp[nxt] % MOD;
            }
            now[i] %= MOD;
        }
        memcpy(dp, now, sizeof(dp));
    }

    cout << dp[0];
}
