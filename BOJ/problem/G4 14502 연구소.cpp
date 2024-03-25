// URL: https://www.acmicpc.net/problem/17141
// Algo: BFS, 조합

// Start:	240325 22 26
// Read:	0 1
// Think:	0 1
// Code:	0 8 연구소2 복붙 후 수정
// Total:	0 10

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
int tile[8][8];
bool visited[8][8];

int dy[4] = {0, 1, 0, -1};
int dx[4] = {1, 0, -1, 0}; // 동남서북
bool OOB(int y, int x) { return y < 0 || y >= n || x < 0 || x >= m; }

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;

    int count = 0;
    vector<pii> vir;
    vector<pii> empt;
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < m; ++j)
        {
            cin >> tile[i][j];
            if (tile[i][j] == 0)
            {
                ++count;
                empt.pb({i, j});
            }
            if (tile[i][j] == 2)
                vir.pb({i, j});
        }
    }

    if (count <= 3)
    {
        cout << 0;
        return 0;
    }

    vector<bool> comb(count);
    for (int i = 0; i < 3; ++i) { comb[i] = true; }

    count -= 3;
    int ans = 0;
    do
    {
        memset(visited, false, sizeof(visited));

        int checked = 0;
        queue<pii> q;
        for (auto [y, x] : vir)
        {
            visited[y][x] = true;
            q.push({y, x});
        }

        for (int i = 0; i < comb.size(); ++i)
        {
            if (!comb[i]) continue;
            tile[empt[i].Y][empt[i].X] = 1;
        }

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
                ++checked;
                q.push({ny, nx});
            }
        }

        ans = max(ans, count - checked);

        for (int i = 0; i < comb.size(); ++i)
        {
            if (!comb[i]) continue;
            tile[empt[i].Y][empt[i].X] = 0;
        }
    }
    while (prev_permutation(all(comb)));

    cout << ans;
}
