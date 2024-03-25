// URL: https://www.acmicpc.net/problem/17142
// Algo: BFS, 조합

// Start:	240325 22 26
// Read:	0 0
// Think:	0 1
// Code:	0 14
// Total:	0 15

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

int n, m;
int tile[50][50];
bool visited[50][50];

int dy[4] = {0, 1, 0, -1};
int dx[4] = {1, 0, -1, 0}; // 동남서북
bool OOB(int y, int x) { return y < 0 || y >= n || x < 0 || x >= n; }

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;

    int count = 0;
    vector<pii> vir;
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            cin >> tile[i][j];
            if (tile[i][j] == 0)
                ++count;
            if (tile[i][j] == 2)
                vir.pb({i, j});
        }
    }

    if (count == 0)
    {
        cout << 0;
        return 0;
    }

    vector<bool> comb(vir.size());
    for (int i = 0; i < m; ++i) { comb[i] = true; }

    int ans = INF;
    do
    {
        memset(visited, false, sizeof(visited));

        int checked = 0;
        queue<pii> q, p;
        for (int i = 0; i < comb.size(); ++i)
        {
            if (!comb[i]) continue;
            visited[vir[i].Y][vir[i].X] = true;
            q.push(vir[i]);
        }

        int dist = 0;
        while (!q.empty())
        {
            ++dist;
            while (!q.empty())
            {
                auto [y, x] = q.front();
                q.pop();

                for (int i = 0; i < 4; ++i)
                {
                    int ny = y + dy[i];
                    int nx = x + dx[i];
                    if (OOB(ny, nx) || visited[ny][nx]) continue;
                    if (tile[ny][nx] == 1) continue;

                    visited[ny][nx] = true;
                    if (tile[ny][nx] == 0) ++checked;
                    p.push({ny, nx});
                }
            }

            if (checked == count)
            {
                ans = min(ans, dist);
                break;
            }

            q.swap(p);
        }
    }
    while (prev_permutation(all(comb)));

    if (ans == INF) cout << -1;
    else cout << ans;
}
