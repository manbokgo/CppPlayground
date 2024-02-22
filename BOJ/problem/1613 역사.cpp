// URL: https://www.acmicpc.net/problem/1613
// Algo: 플로이드

// Start:	240222 17 20
// Read:	0 1
// Think:	0 2
// Code:	0 10
// Total:	

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

constexpr ll  MOD = 1000000007;
constexpr int INF = 0x3f3f3f3f;
constexpr ll  LLINF = 1e18;

bool dist[405][405];

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;

    while (k--)
    {
        int st, en;
        cin >> st >> en;
        dist[st][en] = true;
    }

    for (int i = 1; i <= n; ++i)
    {
        for (int s = 1; s <= n; ++s)
        {
            for (int e = 1; e <= n; ++e)
            {
                if (dist[s][i])
                    dist[s][e] |= dist[s][i] && dist[i][e];
            }
        }
    }

    int t;
    cin >> t;
    while (t--)
    {
        int st, en;
        cin >> st >> en;

        if (dist[st][en]) cout << -1 << "\n";
        else if (dist[en][st]) cout << 1 << "\n";
        else cout << 0 << "\n";
    }
}