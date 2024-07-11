// URL: https://www.acmicpc.net/problem/1113
// Algo: BFS, 시뮬레이션

// Start:	240711 08 25
// Read:	0 2
// Think:	0 7
// Code:	0 10
// Total:	0 19

// 가장 외곽에서 1 높이만 방문, 2 높이만 방문... 하는 BFS를 돌려서
// 도달하지 못하는 곳은 그보다 높은 벽에 둘러쌓인 곳이다.
// 결국에는 벽까지 높이가 되어 그 안쪽 칸까지 방문할 수 있는데
// 이는 그 안쪽 칸이 높아질 수 있는 최대치를 의미함.

// 가장 외곽을 쭉 순회해야하니 귀찮아서 외곽 패딩칸을 만듦
// 마치 모든 칸에 비가 내린다고 생각하여, BFS 돌린 후 '방문되지 않은' 내부 칸 중에
// 높이가 현재 BFS 높이인 것의 높이를 +1 하면서 비가 1칸 채워졌다고 간주하면 됨

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) x.begin(), x.end()
#define pb push_back

using pii = pair<int, int>;

int n, m;
int dy[4] = {0, 1, 0, -1};
int dx[4] = {1, 0, -1, 0}; // 동남서북
bool OOB(int y, int x) { return y < 0 || y >= n + 2 || x < 0 || x >= m + 2; }


char board[52][52];
bool visited[52][52];

int main()
{
    fastio;

    cin >> n >> m;

    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= m; ++j)
        {
            cin >> board[i][j];
            board[i][j] -= '0';
        }
    }

    int answer = 0;
    for (int h = 0; h <= 9; ++h)
    {
        memset(visited, false, sizeof(visited));
        queue<pii> q;

        visited[0][0] = true;
        ++board[0][0];
        q.push({0, 0});

        while (!q.empty())
        {
            const auto [y, x] = q.front();
            q.pop();

            for (int i = 0; i < 4; ++i)
            {
                const int ny = y + dy[i];
                const int nx = x + dx[i];
                if (OOB(ny, nx) || visited[ny][nx]) continue;
                if (board[ny][nx] != h) continue;

                visited[ny][nx] = true;
                ++board[ny][nx];
                q.push({ny, nx});
            }
        }

        for (int i = 1; i <= n; ++i)
        {
            for (int j = 1; j <= m; ++j)
            {
                if (!visited[i][j] && board[i][j] == h)
                {
                    ++board[i][j];
                    ++answer;
                }
            }
        }
    }

    cout << answer;
}
