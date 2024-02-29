// URL: https://www.acmicpc.net/problem/1520
// Algo: 

// Start:	240229 17 30
// Read:	0 0
// Think:	0 2
// Code:	0 4 시간초과
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
using tlll = tuple<ll, ll, ll>;

constexpr int INF = 0x3f3f3f3f;
// constexpr ll  LLINF = 1e18;
// constexpr ll  MOD = 1000000007;

int n, m;

int dy[4] = {0, 1, 0, -1};
int dx[4] = {1, 0, -1, 0}; // 동남서북
bool OOB(int y, int x) { return y < 0 || y >= n || x < 0 || x >= m; }

int tile[505][505];
int answer = 0;
void dfs(int y, int x)
{
    if (y == n - 1 && x == m - 1)
    {
        ++answer;
        return;
    }

    for (int i = 0; i < 4; ++i)
    {
        int ny = y + dy[i];
        int nx = x + dx[i];
        if (OOB(ny, nx)) continue;
        if (tile[y][x] <= tile[ny][nx]) continue;

        dfs(ny, nx);
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < m; ++j)
        {
            cin >> tile[i][j];
        }
    }

    dfs(0, 0);
    cout << answer;
}
