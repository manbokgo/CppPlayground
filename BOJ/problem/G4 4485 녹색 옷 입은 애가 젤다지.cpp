// URL: https://www.acmicpc.net/problem/4485
// Algo: 다익스트라

// Start:	240224 20 26
// Read:	0 1
// Think:	0 0
// Code:	0 14
// Total:	0 15

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

int dy[4] = {0, 1, 0, -1};
int dx[4] = {1, 0, -1, 0}; // 우하좌상

int tile[126][126];
int d[126][126];

int n;

bool OOB(int y, int x)
{
    return y < 0 || y >= n || x < 0 || x >= n;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 0;
    while (true)
    {
        ++t;

        cin >> n;
        if (n == 0) return 0;

        memset(d, INF, sizeof(d));
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                cin >> tile[i][j];
            }
        }

        // {비용, y, x}
        priority_queue<tiii, vector<tiii>, greater<>> pq;

        d[0][0] = tile[0][0];
        pq.push({d[0][0], 0, 0});

        while (!pq.empty())
        {
            auto [dist, y, x] = pq.top();
            pq.pop();

            if (d[y][x] != dist) continue;

            for (int i = 0; i < 4; ++i)
            {
                int ny = y + dy[i];
                int nx = x + dx[i];
                if (OOB(ny, nx)) continue;
                int nDist = tile[ny][nx];

                if (d[ny][nx] <= d[y][x] + nDist) continue;
                d[ny][nx] = d[y][x] + nDist;
                pq.push({d[ny][nx], ny, nx});
            }
        }

        cout << "Problem " << t << ": " << d[n-1][n-1] << "\n";
    }
}
