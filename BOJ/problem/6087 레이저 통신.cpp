// URL: https://www.acmicpc.net/problem/6087
// Algo: BFS

// Start:	240302 19 45
// Read:	0 0
// Think:	0 44
// Code:	0 16
// Total:	1 0

// 처음엔 A*처럼 휴리스틱 만들어서 도착지로 가는 가장 짧은 경로상의 타일만 택하되,
// 현재 움직이고 있는 방향과 지금까지 꺾인 횟수를 아는 상태에서 현재 타일의 앞,좌,우 3방향을 pq에 넣고,
// pq를 통해 앞 타일에 먼저 방문해서 다시 3방향을 pq에 넣고, 한 칸씩 한 칸씩 반복하는...
//
// 그런 요상한 방법으로 한 30분 생각했는데 너무 복잡한 거 같아서 그림판 놓고 여러 경우 곰곰히 생각하다보니
// 근본적으로 선분들의 개수를 세는 것이고, 어떤 타일을 첫 방문할 때의 선분이 최소 선분이니
// 선분을 가능한 끝까지 쭉쭉 그리면서, 시작점으로부터 선분 1개, 2개, 3개.. 단계로 BFS를 돌리면 더 간단함을 깨닫고 풀음
//
// + 맨처음 구상대로 구현해봄. 예상한대로 생각하기 까다로운 부분들이 많아서 실수 와장창하다가 제대로 된 구현하는데 1시간 걸림
// 일단 휴리스틱은 애초에 잘못된 시도. 문제 자체 의도가 거리는 좀 더 멀더라도 거울 수는 적은 경우가 분명 있다.
// 막연히 이게 없으면 연산이 미친듯이 불어날 거 같아서 넣은건데, 생각해보니 겨우 100x100 타일 밖에 없다..
//
// 다익스트라도 선분 풀이법과 원리는 크게 다르지 않으나
// 선분은 한 방향으로 끝까지 쭉쭉 가고, 다익스트라는 한 칸씩 가는게 차이.
//
// ***.**
// ↑→→→→→
// ↑**↑**
// C→→→**
//
// 이 상황에서 꺾인횟수 1짜리를 돌 때, 위 방향으로 갈 때 앞 칸에 꺾인횟수 1이 채워져 있긴 하지만
// 그걸 뛰어넘어서 [0,3] 칸에 도달해야 하므로 [1,3]이 꺾인횟수가 같아도 일단 pq에 넣도록 해야한다.
// 그렇게 추가된 [1,3]이 돌 때는 [1,2], [1,4]에는 꺾인횟수가 이미 더 작은 값으로 채워져있으므로
// pq에 넣지 않고 스킵하고 [0,3]만 pq에 넣어지게 되는 식으로 진행했는데...
//
// ↑→→*.
// C*...
// ↓→→*.
// https://www.acmicpc.net/board/view/109356
//
// 저격 케이스가 있었다. 위처럼 →,↑처럼 서로 방향이 다른게 교차하는 경우면 별 문제가 없으나
// 이 케이스처럼 ↓,↑ 마주 보는 방향으로 교차하면 중복으로 pq에 들어가는 문제가 생김.
// [1,2]칸이 pq에 중복으로 2개 들어가고, 그 둘이 똑같이 [1,3]을 2개 추가하는 것이 반복되면서
// 메모리를 폭파시켜버림. 이걸 해결하려면 [1,3]처럼 꺾인횟수가 같은데 진행방향도 같으면 스킵하는 로직이 또 필요.
//
// 엄청나게 번거롭다 진짜. 처음부터 깔끔한 풀이를 생각하도록 노력하자.

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
using tiiii = tuple<int, int, int, int>;
using tlll = tuple<ll, ll, ll>;

constexpr int INF = 0x3f3f3f3f;
// constexpr ll  LLINF = 1e18;
// constexpr ll  MOD = 1000000007;

int n, m;

int  dy[4] = {0, 1, 0, -1};
int  dx[4] = {1, 0, -1, 0}; // 동남서북
bool OOB(int y, int x) { return y < 0 || y >= n || x < 0 || x >= m; }

int tile[100][100];
int dirs[100][100];

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> m >> n;
    memset(tile, -1, sizeof(tile));
    memset(dirs, -1, sizeof(dirs));

    vector<pii> C;
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < m; ++j)
        {
            char c;
            cin >> c;
            if (c == 'C')
            {
                C.pb({i, j});
            }
            else if (c == '*')
            {
                tile[i][j] = INF;
            }
        }
    }

    priority_queue<tiiii, vector<tiiii>, greater<>> pq;
    for (int i = 0; i < 4; ++i)
    {
        int ny = C[1].Y + dy[i];
        int nx = C[1].X + dx[i];
        if (OOB(ny, nx)) continue;
        if (tile[ny][nx] == INF) continue;

        tile[ny][nx] = 0;
        pq.push({0, ny, nx, i});
    }

    while (!pq.empty())
    {
        auto [count, y, x, dir] = pq.top();
        pq.pop();

        if (y == C[0].Y && x == C[0].X)
        {
            cout << count;
            return 0;
        }

        for (int i = 0; i < 4; ++i)
        {
            if (i == (dir + 2) % 4) continue;

            int ny = y + dy[i];
            int nx = x + dx[i];
            if (OOB(ny, nx)) continue;
            if (tile[ny][nx] == INF) continue;

            int nCount = i == dir ? count : count + 1;
            if (-1 < tile[ny][nx] && tile[ny][nx] < nCount) continue;
            if (tile[ny][nx] == nCount && dirs[ny][nx] == i) continue;

            tile[ny][nx] = nCount;
            dirs[ny][nx] = i;
            pq.push({nCount, ny, nx, i});
        }
    }
}
