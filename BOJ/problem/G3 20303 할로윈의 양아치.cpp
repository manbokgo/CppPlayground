// URL: https://www.acmicpc.net/problem/20303
// Algo: 분리 집합, DP (0-1 배낭 문제)

// Start:	240822 13 43
// Read:	0 1
// Think:	0 5
// Code:	0 14
// Total:	0 20

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) x.begin(), x.end()
#define pb push_back

using pii = pair<int, int>;

int candy[30'001];
int p[30'001];
int dp[3'001];

int Find(int a)
{
    if (p[a] < 0) return a;
    return p[a] = Find(p[a]);
}

bool Union(int a, int b)
{
    int ap = Find(a);
    int bp = Find(b);
    if (ap == bp) return false;

    if (-p[ap] < -p[bp]) swap(ap, bp);
    p[ap] += p[bp];
    p[bp] = ap;

    candy[ap] += candy[bp];
    candy[bp] = 0;
    return true;
}

int main()
{
    fastio;
    memset(p, -1, sizeof(p));

    int n, m, k;
    cin >> n >> m >> k;
    for (int i = 1; i <= n; ++i)
    {
        cin >> candy[i];
    }
    while (m--)
    {
        int a, b;
        cin >> a >> b;
        Union(a, b);
    }

    vector<pii> sacks;
    for (int i = 1; i <= n; ++i)
    {
        if (p[i] < 0)
            sacks.pb({-p[i], candy[i]});
    }

    // 배낭
    for (const auto [w, v] : sacks)
    {
        for (int j = k - 1; j >= w; --j)
            dp[j] = max(dp[j], v + dp[j - w]);
    }

    cout << dp[k - 1];
}
