// URL: https://www.acmicpc.net/problem/6087
// Algo: BFS

// Start:	240302 19 45
// Read:	0 0
// Think:	0 44
// Code:	0 16
// Total:	1 0

// A*처럼 휴리스틱 넣어서 C에서 C로 가는 가장 짧은 경로대로 일직선으로 쭉쭉 가다가, 막히면 방향이 꺾으면서 카운팅하는...
// 그런 식의 방법으로 한 30분 생각했는데 너무 복잡한 거 같아서 그림판 놓고 여러 경우 곰곰히 생각하다보니
// 근본적으로 선분들의 개수를 세는 것이고, 선분을 하나씩 늘려나가는 단계로 BFS를 돌리면
// 간단하게 어떤 타일을 첫 방문할 때의 선분이 최단 선분임을 깨닫고 풀음. 괜히 거울 최솟값을 구하라는게 아니었다.

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

int n, m;

int  dy[4] = {0, 1, 0, -1};
int  dx[4] = {1, 0, -1, 0}; // 동남서북
bool OOB(int y, int x) { return y < 0 || y >= n || x < 0 || x >= m; }

char tile[100][100];
int  line[100][100];

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> m >> n;
    memset(line, -1, sizeof(line));

    vector<pii> C;
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < m; ++j)
        {
            cin >> tile[i][j];
            if (tile[i][j] == 'C') C.pb({i, j});
        }
    }

    queue<pii> q;
    line[C[0].Y][C[0].X] = 0;
    q.push(C[0]);
    while (!q.empty())
    {
        auto [y, x] = q.front();
        q.pop();
        for (int i = 0; i < 4; ++i)
        {
            int ny = y + dy[i];
            int nx = x + dx[i];

            while (!OOB(ny, nx) && tile[ny][nx] != '*')
            {
                if (line[ny][nx] == -1)
                {
                    line[ny][nx] = line[y][x] + 1;
                    q.push({ny, nx});

                    if (ny == C[1].Y && nx == C[1].X)
                    {
                        cout << line[C[1].Y][C[1].X] - 1;
                        return 0;
                    }
                }

                ny += dy[i];
                nx += dx[i];
            }
        }
    }
}
