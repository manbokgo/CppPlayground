// URL: https://www.acmicpc.net/problem/11559
// Algo: 시뮬레이션, BFS

// Start:	240718 13 30
// Read:	0 2
// Think:	0 2
// Code:	0 22
// Total:	0 26

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) x.begin(), x.end()
#define pb push_back

using pii = pair<int, int>;

int dy[4] = {0, 1, 0, -1};
int dx[4] = {1, 0, -1, 0}; // 동남서북
bool OOB(int y, int x) { return y < 0 || y >= 12 || x < 0 || x >= 6; }

char board[12][6];
bool visited[12][6];

bool BFS(int iy, int ix)
{
    const char target = board[iy][ix];

    queue<pii> q;
    vector<pii> tmp;
    tmp.reserve(16);

    visited[iy][ix] = true;
    q.push({iy, ix});
    tmp.pb({iy, ix});

    int cnt = 0;
    while (!q.empty())
    {
        const auto [y, x] = q.front();
        q.pop();

        for (int i = 0; i < 4; ++i)
        {
            const int ny = y + dy[i];
            const int nx = x + dx[i];
            if (OOB(ny, nx) || visited[ny][nx] || board[ny][nx] != target) continue;
            visited[ny][nx] = true;
            q.push({ny, nx});
            tmp.pb({ny, nx});
        }
    }

    if (tmp.size() >= 4)
    {
        for (const auto [y, x] : tmp)
        {
            board[y][x] = '.';
        }

        return true;
    }

    return false;
}

int main()
{
    fastio;

    for (int y = 0; y < 12; ++y)
        for (int x = 0; x < 6; ++x)
            cin >> board[y][x];

    int answer = 0;
    while (true)
    {
        memset(visited, false, sizeof(visited));

        bool broke = false;
        for (int y = 0; y < 12; ++y)
        {
            for (int x = 0; x < 6; ++x)
            {
                if (board[y][x] != '.' && !visited[y][x])
                    broke |= BFS(y, x);
            }
        }
        if (!broke) break;


        vector<char> moveBuffer;
        moveBuffer.reserve(12);
        for (int x = 0; x < 6; ++x)
        {
            moveBuffer.clear();
            for (int y = 11; y >= 0; --y)
            {
                if (board[y][x] != '.')
                    moveBuffer.pb(board[y][x]);
            }

            for (int y = 11; y >= 0; --y)
            {
                if (11 - y < moveBuffer.size()) board[y][x] = moveBuffer[11 - y];
                else board[y][x] = '.';
            }
        }

        ++answer;
    }

    cout << answer;
}
