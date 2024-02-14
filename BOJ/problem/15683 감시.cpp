// URL: https://www.acmicpc.net/problem/15683
// Algo: 시뮬레이션, 백트래킹(DFS)

// 그리디로 당장 가장 많이 사각지대를 밝힐 수 있는 최선 방향으로 쭉 했는데
// 생각이 짧았다. 틀림. 당장 최선이 아니더라도 정답이 될 수 있다. 백트래킹으로 해야 함.

// https://blog.encrypted.gg/948
// 바킹독 선생의 풀이대로 direction을 enum 같은거로 두지 말고
// int dx[4] = {1,0,-1,0};
// int dy[4] = {0,1,0,-1}; // 남쪽, 동쪽, 북쪽, 서쪽 순서
// dx, dy의 값을 더하면서, OBB로 경계 넘거나 벽 만나면 멈춰서
// 그동안 몇 타일을 밝혀냈는지 세는 방식이 깔끔하다. 멍청함.

// stack으로 재귀 깊이를 측정했는데, 그냥 CCTV 좌표를 쭉 넣은 vector<pii>에 깊이로 인덱스로 참조하게 하고
// 깊이가 CCTV 개수와 같아지면 return하면 간단한 거였음. 백트래킹은 좀 풀어봐야 한다. 멍청함.

// 위 2가지 수정함. 이전 코딩은 커밋 참고. 시간은 44ms로 동일하게 나온다.
// 이전 상태 백업용으로 벡터 사용했는데 동적할당 때문에 성능이 좀 낮은 듯

// 또한 DFS로 백트래킹을 진행했는데
// 4진법으로 각 CCTV의 4가지 방향을 조합한 모든 경우의 수를 구하는 방법이 참 세련됨

// Start:	240213 23 32
// Read:	23 33
// Think:	23 37
// Code:	00 50
// Total:	1 18

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


int n, m;

int dx[4] = {1, 0, -1, 0};
int dy[4] = {0, 1, 0, -1}; // 동남서북

vector<pii> cctv;
vector<pii> listOfFive;

bool OOB(int y, int x)
{
    return y < 0 || y >= n || x < 0 || x >= m;
}

int view(int y, int x, int dir, vector<vector<int>>& tile)
{
    int blind = 0;

    dir %= 4;
    while (true)
    {
        y += dy[dir];
        x += dx[dir];
        if (OOB(y, x) || tile[y][x] == 6) break;
        if (tile[y][x] != 0) continue;
        tile[y][x] = -1;
        ++blind;
    }

    return blind;
}


int solve(int depth, int blind, vector<vector<int>>& tile)
{
    if (depth == cctv.size())
    {
        return blind;
    }

    auto [y, x] = cctv[depth];

    int bestBlind = blind;
    for (int k = 0; k < 4; ++k)
    {
        auto prevTile = tile;
        int  thisBlind = 0;

        if (tile[y][x] == 4)
        {
            thisBlind += view(y, x, k + 0, tile);
            thisBlind += view(y, x, k + 1, tile);
            thisBlind += view(y, x, k + 2, tile);
        }
        else if (tile[y][x] == 3)
        {
            thisBlind += view(y, x, k + 0, tile);
            thisBlind += view(y, x, k + 1, tile);
        }
        else if (tile[y][x] == 2)
        {
            if (k >= 2) continue;
            thisBlind += view(y, x, k + 0, tile);
            thisBlind += view(y, x, k + 2, tile);
        }
        else if (tile[y][x] == 1)
        {
            thisBlind += view(y, x, k + 0, tile);
        }

        int availBlind = solve(depth + 1, blind - thisBlind, tile);
        if (availBlind == 0)
        {
            cout << "0";
            exit(0);
        }

        if (availBlind < bestBlind)
        {
            bestBlind = availBlind;
        }
        tile = prevTile;
    }


    return bestBlind;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    int blind = n * m;

    vector<vector<int>> tile(n, vector<int>(m));

    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < m; ++j)
        {
            cin >> tile[i][j];
            if (tile[i][j] > 0)
            {
                --blind;
                if (tile[i][j] <= 4) cctv.pb({i, j});
                if (tile[i][j] == 5) listOfFive.pb({i, j});
            }
        }
    }

    // 5 처리
    for (auto [y, x] : listOfFive)
    {
        for (int k = 0; k < 4; ++k)
        {
            blind -= view(y, x, k, tile);
        }
    }

    cout << solve(0, blind, tile);
    return 0;
}
