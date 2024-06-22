// URL: https://www.acmicpc.net/problem/16985
// Algo: 브루트포스, 순열, BFS, DFS

// Start:	240621 11 08
// Read:	0 2
// Think:	0 11
// Code:	0 56
// Total:	1 9

// 어떻게 해야할 지는 알겠는데 설계나 구현력이 모자랐다.
// visited 배열 따로 없이 board에 visited를 기록하려다가
// 그럼 회전할 때마다 싹 초기화해야 하니 번거로워 그냥 visited 배열 쓰는 걸로 바꾸고,
// next_permutation 쓰려다가 어차피 쓰는 DFS에 순열 결정 로직을 통합하는 등 변경점이 많았음
// 수련이 더 필요함

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) x.begin(), x.end()
#define pb push_back

using tiii = tuple<int, int, int>;
constexpr int INF = 0x3f3f3f3f;

bool board[5][5][5];
bool org[5][5][5];
int visited[5][5][5];
bool selected[5];

int dz[6] = {0, 0, 0, 0, 1, -1};
int dy[6] = {0, 1, 0, -1, 0, 0};
int dx[6] = {1, 0, -1, 0, 0, 0}; // 동남서북아위
bool OOB(int z, int y, int x) { return z < 0 || z >= 5 || y < 0 || y >= 5 || x < 0 || x >= 5; }

int answer = INF;

void Rotate(int z)
{
    bool tmp[5][5];
    memcpy(tmp, board[z], sizeof(tmp));
    memset(board[z], false, sizeof(board[z]));
    for (int y = 0; y < 5; ++y)
    {
        for (int x = 0; x < 5; ++x)
        {
            if (tmp[y][x])
                board[z][x][4 - y] = true;
        }
    }
}

int BFS()
{
    memset(visited, -1, sizeof(visited));

    queue<tiii> q;
    visited[0][0][0] = 0;
    q.push({0, 0, 0});

    while (!q.empty())
    {
        const auto [z, y, x] = q.front();
        q.pop();

        for (int i = 0; i < 6; ++i)
        {
            const int nz = z + dz[i];
            const int ny = y + dy[i];
            const int nx = x + dx[i];
            if (OOB(nz, ny, nx) ||
                !board[nz][ny][nx] ||
                visited[nz][ny][nx] != -1)
                continue;

            visited[nz][ny][nx] = visited[z][y][x] + 1;
            if (nz == 4 && ny == 4 && nx == 4) return visited[nz][ny][nx];
            q.push({nz, ny, nx});
        }
    }

    return INF;
}

void DFS(int depth)
{
    if (depth == 5)
    {
        if (board[0][0][0] && board[4][4][4])
        {
            answer = min(answer, BFS());
            if (answer == 12)
            {
                cout << answer;
                exit(0);
            }
        }
        return;
    }

    for (int i = 0; i < 5; ++i)
    {
        if (selected[i]) continue;
        selected[i] = true;
        memcpy(board[depth], org[i], sizeof(board[depth]));

        for (int rotate = 0; rotate < 4; ++rotate)
        {
            Rotate(depth);
            DFS(depth + 1);
        }

        selected[i] = false;
    }
}


int main()
{
    fastio;

    for (int z = 0; z < 5; ++z)
    {
        for (int y = 0; y < 5; ++y)
        {
            for (int x = 0; x < 5; ++x)
            {
                cin >> org[z][y][x];
            }
        }
    }

    DFS(0);
    cout << (answer != INF ? answer : -1);
}
