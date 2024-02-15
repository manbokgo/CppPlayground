// URL: https://www.acmicpc.net/problem/11404
// Algo: 플로이드 기본

// Start:	240206 23 20
// Read:	0 0
// Think:	0 0
// Code:	0 11
// Total:	0 11

#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define X first
#define Y second
#define all(x) x.begin(), x.end()
#define sortvec(x) sort(all(x))
#define compress(x) x.erase(unique(all(x)), x.end())
#define findvec(x, value) find(all(x), value) != x.end()

using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;

const ll  MOD = 1000000007;
const int INF = 0x3f3f3f3f;
const ll  LLINF = 1e18;

int dist[101][101];

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    cin >> N >> M;

    for (int i = 1; i <= N; ++i)
    {
        fill(dist[i] + 1, dist[i] + N + 1, INF);
    }

    while (M--)
    {
        int a, b, c;
        cin >> a >> b >> c;
        dist[a][b] = min(dist[a][b], c);
    }

    for (int k = 1; k <= N; ++k)
    {
        dist[k][k] = 0;
        for (int s = 1; s <= N; ++s)
        {
            for (int e = 1; e <= N; ++e)
            {
                dist[s][e] = min(dist[s][e], dist[s][k] + dist[k][e]);
            }
        }
    }

    for (int s = 1; s <= N; ++s)
    {
        for (int e = 1; e <= N; ++e)
        {
            if (dist[s][e] == INF) cout << "0 ";
            else cout << dist[s][e] << " ";
        }

        cout << "\n";
    }
}
