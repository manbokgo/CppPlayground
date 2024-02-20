// URL: https://www.acmicpc.net/problem/16236
// Algo: BFS, 시뮬레이션

// Start:	240221 00 16
// Read:	0 1
// Think:	0 4
// Code:	0 30
// 상좌우하 순의 BFS로는 시작 타일의 맨오른쪽이 먼저 처리되지 않는다는 점에 헤맴. 생각을 좀 더 하고 시작하자.
// 거리별로 후보자들 저장했다가 가장 상, 좌를 찾아야함
// Code:	0 15
// Total:	0 50

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

int  N;
int  tiles[25][25];
bool visited[25][25];
int  sharkLevel = 2;
int  sharkFeed = 0;
int  answer = 0;

int dy[4] = {-1, 0, 0, 1};
int dx[4] = {0, -1, 1, 0}; // 상좌우하

struct tile
{
    int y;
    int x;
    int dist;
};

bool OOB(int y, int x)
{
    return y < 0 || y >= N || x < 0 || x >= N;
}

void BFS(int startY, int startX)
{
    queue<tile> q;

    memset(visited, false, sizeof(visited));
    visited[startY][startX] = true;
    q.push({startY, startX, 0});

    int         lastDist = 0;
    vector<pii> candidates;
    while (!q.empty())
    {
        auto [y, x, dist] = q.front();
        q.pop();

        // 1거리 순회 후 이제 2거리를 시작함
        // 이때 lastDist = 1, dist = 2
        // 1거리 순회 중에 찾은 모든 2거리 후보자 중에서
        // 가장 상,좌의 후보자를 찾아서 이동함 (그곳까지의 거리는 dist(=2))
        if (dist > lastDist)
        {
            if (!candidates.empty())
            {
                int fY = INF;
                int fX = INF;
                for (auto [cY, cX] : candidates)
                {
                    if (cY < fY || (cY == fY && cX < fX))
                    {
                        fY = cY;
                        fX = cX;
                    }
                }

                tiles[fY][fX] = 0;

                ++sharkFeed;
                if (sharkFeed == sharkLevel)
                {
                    sharkFeed = 0;
                    ++sharkLevel;
                }

                answer += dist;
                BFS(fY, fX);
                return;
            }
            else
            {
                lastDist = dist;
            }
        }

        for (int i = 0; i < 4; ++i)
        {
            int ny = y + dy[i];
            int nx = x + dx[i];

            if (OOB(ny, nx)) continue;
            if (visited[ny][nx]) continue;
            if (tiles[ny][nx] > sharkLevel) continue;

            if (0 < tiles[ny][nx] && tiles[ny][nx] < sharkLevel)
                candidates.pb({ny, nx});

            visited[ny][nx] = true;
            q.push({ny, nx, dist + 1});
        }
    }

    return; // 엄마 불러!!!!
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N;

    int startY = 0;
    int startX = 0;

    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            cin >> tiles[i][j];
            if (tiles[i][j] == 9)
            {
                tiles[i][j] = 0; // 9 그대로 넣으면 안되는 점 유의
                startY = i;
                startX = j;
            }
        }
    }

    BFS(startY, startX);
    cout << answer;
}
