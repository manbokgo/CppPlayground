// URL: https://www.acmicpc.net/problem/14500
// Algo: DFS, 브루트포스

// Start:	250122 11 23
// Read:	0 1
// Think:	0 3
// Code:	0 14
// Total:	0 18

// 모든 칸에 DFS를 돌려서 가능한 모든 경우를 찾는다.
// T자 모형 블럭은 DFS를 따라가서는 찾을 수 없어 따로 찾아줘야 하는데,
// OOB가 걸릴 경우 어떻게 처리해야 하는 지를 잘못해서 많이 헤맴.
// OOB라면 minVal을 0으로 해주어야 한다.

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) x.begin(), x.end()
#define pb push_back

constexpr int INF = 0x3f3f3f3f;

int n, m;
int dy[4] = {0, 1, 0, -1};
int dx[4] = {1, 0, -1, 0}; // 동남서북
inline bool OOB(int y, int x) { return y < 0 || y >= n || x < 0 || x >= m; }

int board[500][500];
bool visited[500][500];
int ans = 0;

void DFS(int y, int x, int depth, int sum)
{
    sum += board[y][x];
    if (depth == 4)
    {
        ans = max(ans, sum);
        return;
    }

    visited[y][x] = true;
    for (int dir = 0; dir < 4; ++dir)
    {
        const int ny = y + dy[dir];
        const int nx = x + dx[dir];
        if (OOB(ny, nx) || visited[ny][nx]) continue;
        DFS(ny, nx, depth + 1, sum);
    }
    visited[y][x] = false;
}

void CheckT(int y, int x)
{
    int sum = board[y][x];
    int minVal = INF;
    for (int i = 0; i < 4; ++i)
    {
        const int ny = y + dy[i];
        const int nx = x + dx[i];
        if (OOB(ny, nx))
        {
            minVal = 0;
            continue;
        };

        sum += board[ny][nx];
        minVal = min(minVal, board[ny][nx]);
    }
    ans = max(ans, sum - minVal);
}

int main()
{
    fastio;

    cin >> n >> m;
    for (int y = 0; y < n; ++y)
    {
        for (int x = 0; x < m; ++x)
        {
            cin >> board[y][x];
        }
    }

    for (int y = 0; y < n; ++y)
    {
        for (int x = 0; x < m; ++x)
        {
            DFS(y, x, 1, 0);
            CheckT(y, x);
        }
    }

    cout << ans;
}
