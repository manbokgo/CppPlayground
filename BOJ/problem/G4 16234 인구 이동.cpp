// URL: https://www.acmicpc.net/problem/16234
// Algo: 시뮬레이션, BFS

// Start:	240902 14 07
// Read:	0 1
// Think:	0 1
// Code:	0 14
// Total:	0 16

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) x.begin(), x.end()
#define pb push_back

using pii = pair<int, int>;

int n, L, R;
int board[50][50];
bool visited[50][50];

int dy[4] = {0, 1, 0, -1};
int dx[4] = {1, 0, -1, 0}; // 동남서북
bool OOB(int y, int x) { return y < 0 || y >= n || x < 0 || x >= n; }


int main()
{
    fastio;
    cin >> n >> L >> R;
    for (int y = 0; y < n; ++y)
    {
        for (int x = 0; x < n; ++x)
        {
            cin >> board[y][x];
        }
    }

    int answer = 0;
    while (true)
    {
        memset(visited, false, sizeof(visited));
        bool changed = false;

        for (int y = 0; y < n; ++y)
        {
            for (int x = 0; x < n; ++x)
            {
                if (visited[y][x]) continue;

                queue<pii> q;
                visited[y][x] = true;
                q.push({y, x});

                int sum = 0;
                vector<pii> moves;
                while (!q.empty())
                {
                    const auto [cy, cx] = q.front();
                    q.pop();
                    sum += board[cy][cx];
                    moves.pb({cy, cx});

                    for (int i = 0; i < 4; ++i)
                    {
                        const int ny = cy + dy[i];
                        const int nx = cx + dx[i];
                        if (OOB(ny, nx) || visited[ny][nx]) continue;

                        const int diff = abs(board[ny][nx] - board[cy][cx]);
                        if (L <= diff && diff <= R)
                        {
                            visited[ny][nx] = true;
                            q.push({ny, nx});
                        }
                    }
                }

                if (moves.size() > 1)
                {
                    changed = true;
                    const int result = sum / moves.size();
                    for (const auto [cy, cx] : moves)
                        board[cy][cx] = result;
                }
            }
        }

        if (!changed) break;
        ++answer;
    }

    cout << answer;
}
