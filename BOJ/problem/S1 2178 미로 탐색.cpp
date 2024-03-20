// URL: https://www.acmicpc.net/problem/2178
// Algo: BFS 길찾기(비용 일괄1)

// Start:	240218 01 54
// Read:	0 0
// Think:	0 0
// Code:	0 16
// Total:	0 16

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

constexpr ll  MOD = 1000000007;
constexpr int INF = 0x3f3f3f3f;
constexpr ll  LLINF = 1e18;

int tile[105][105];
bool visited[105][105];

int dy[4] = {0, 1, 0, -1};
int dx[4] = {1, 0, -1, 0};

int N, M;

bool OOB(int y, int x)
{
    return y < 0 || y >= N || x < 0 || x >= M;
}

int BFS()
{
    queue<pii> q;

    visited[0][0] = true;
    q.push({0, 0});

    while (!q.empty())
    {
        auto [y, x] = q.front();
        q.pop();

        if (y == N-1  && x == M-1)
        {
            return tile[y][x];
        }

        for (int i = 0; i < 4; ++i)
        {
            int ny = y + dy[i];
            int nx = x + dx[i];

            if (OOB(ny, nx)) continue;
            if (tile[ny][nx])
            {
                if (visited[ny][nx]) continue;

                tile[ny][nx] = tile[y][x] + 1;

                visited[ny][nx] = true;
                q.push({ny, nx});
            }
        }
    }

    return -1; // Fucked
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N >> M;
    for (int i = 0; i < N; ++i)
    {
        string txt;
        cin >> txt;
        for (int j = 0; j < M; ++j)
        {
            tile[i][j] = txt[j] - '0';
        }
    }

    cout << BFS();
}
