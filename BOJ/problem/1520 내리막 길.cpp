// URL: https://www.acmicpc.net/problem/1520
// Algo: DP, DFS

// Start:	240229 17 30
// Read:	0 0
// Think:	0 2
// Code:	0 4 DFS 시간초과
// Code:	0 10 +DP 시간초과
// Code:	0 5 dp 초기값 -1로 변경
// Total:	0 21

// 한번 방문한 타일도 재방문할 수 있으니 DFS 시간복잡도가 O(5V)가 아니라 최소 O(V^2)이다.
// 그냥 DFS 만으로는 풀 수 없고 DP가 들어가야함. 미리 좀 생각하고 풀자.

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
int dp[505][505];

int dfs(int y, int x)
{
    // 실수: dp=0 이어도 바로 리턴해야함
    if (dp[y][x] >= 0) return dp[y][x];

    dp[y][x] = 0;
    for (int i = 0; i < 4; ++i)
    {
        int ny = y + dy[i];
        int nx = x + dx[i];
        if (OOB(ny, nx)) continue;
        if (tile[y][x] <= tile[ny][nx]) continue;

        dp[y][x] += dfs(ny, nx);
    }

    return dp[y][x];
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

    memset(dp, -1, sizeof(dp));
    dp[n-1][m-1] = 1;
    dfs(0, 0);
    cout << dp[0][0];
}
