// URL: https://www.acmicpc.net/problem/17135
// Algo: 시뮬레이션, BFS

// Start:	240307 18 35
// Read:	0 1
// Think:	0 3
// Code:	0 37  388ms 정답이긴한데 왜 이리 시간 오래 걸리지?
// Total:	0 40

// + Code:    0 10 4ms
// 무지성으로 compressVec 써서 느렸던 듯? 그냥 중복삭제 없이 순회하고 이미 지워진거면 스킵하는 식으로 바꿈.
// 진짜로 타일에서 적을 한 칸씩 내려버릴 필요 없음. Move() 함수 삭제.
// BFS가 아래로는 방문 안하는만큼, 마치 궁수들이 한 칸씩 위로 올라가는 것처럼
// 타일은 그대로두고 BFS 시작 지점을 한 칸씩 위로 올리면 됨

// 16236 아기 상어 문제는 가장 위 + 가장 왼쪽 조건이라 BFS 도중 찾자마자 return 하면 안 되고
// 일단 후보자들을 다 모아서 그 중 가장 위에서 가장 왼쪽을 찾아야했지만
// 이 문제는 단순히 가장 왼쪽 조건이라  서북동 순으로 접근해서 바로 return 가능


#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define Y first
#define X second
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

int dy[3] = {0, -1, 0};
int dx[3] = {-1, 0, 1}; // 서북동

int  n, m, range;
int  otile[15][15];
int  tile[15][15];
bool visited[15][15];

bool OOB(int y, int x) { return y < 0 || y >= n || x < 0 || x >= m; }

pii BFS(int stY, int stX)
{
    memset(visited, false, sizeof(visited));
    queue<tiii> q; // y, x, 거리

    visited[stY][stX] = true;
    q.push({stY, stX, 1});

    while (!q.empty())
    {
        auto [y, x, dist] = q.front();
        q.pop();

        if (tile[y][x]) return {y, x};
        if (dist == range) continue;

        for (int i = 0; i < 3; ++i)
        {
            int ny = y + dy[i];
            int nx = x + dx[i];
            int nDist = dist + 1;

            if (OOB(ny, nx)) continue;
            visited[ny][nx] = true;
            q.push({ny, nx, nDist});
        }
    }

    return {INF, INF};
}


int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m >> range;
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < m; ++j)
        {
            cin >> otile[i][j];
        }
    }

    vector<bool> archers(m, true);
    for (int i = 0; i < 3; ++i)
    {
        archers[i] = false;
    }

    int answer = 0;
    do
    {
        int removed = 0;
        int stY = n;
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < m; ++j)
            {
                tile[i][j] = otile[i][j];
            }
        }

        while (--stY)
        {
            vector<pii> enemyToRemove;
            for (int i = 0; i < m; ++i)
            {
                if (!archers[i])
                {
                    auto [y, x] = BFS(stY, i);
                    if (y != INF) enemyToRemove.pb({y, x});
                }
            }

            for (auto [y, x] : enemyToRemove)
            {
                if (!tile[y][x]) continue;
                ++removed;
                tile[y][x] = 0;
            }
        }

        answer = max(answer, removed);
    }
    while (next_permutation(all(archers)));

    cout << answer;
}
