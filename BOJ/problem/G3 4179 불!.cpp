// URL: https://www.acmicpc.net/problem/4179
// Algo: BFS

// Start:	240828 15 15
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

int n, m;
char board[1000][1000];

int dy[4] = {0, 1, 0, -1};
int dx[4] = {1, 0, -1, 0}; // 동남서북
bool OOB(int y, int x) { return y < 0 || y >= n || x < 0 || x >= m; }


int main()
{
    fastio;
    cin >> n >> m;

    queue<pii> player;
    queue<pii> fires;
    for (int y = 0; y < n; ++y)
    {
        for (int x = 0; x < m; ++x)
        {
            cin >> board[y][x];
            if (board[y][x] == 'J') player.push({y, x});
            else if (board[y][x] == 'F') fires.push({y, x});
        }
    }

    int turn = 0;
    while (true)
    {
        size_t fsz = fires.size();
        while (fsz--)
        {
            const auto [fy, fx] = fires.front();
            fires.pop();

            for (int i = 0; i < 4; ++i)
            {
                const int ny = fy + dy[i];
                const int nx = fx + dx[i];

                if (OOB(ny, nx) || board[ny][nx] == '#' || board[ny][nx] == 'F') continue;
                board[ny][nx] = 'F';
                fires.push({ny, nx});
            }
        }

        size_t psz = player.size();
        while (psz--)
        {
            const auto [py, px] = player.front();
            player.pop();

            if (py == 0 || py == n-1 || px == 0 || px == m-1)
            {
                cout << turn + 1;
                return 0;
            }

            for (int i = 0; i < 4; ++i)
            {
                const int ny = py + dy[i];
                const int nx = px + dx[i];

                if (OOB(ny, nx) || board[ny][nx] != '.') continue;
                board[ny][nx] = 'J';
                player.push({ny, nx});
            }
        }

        if (player.empty())
        {
            cout << "IMPOSSIBLE";
            return 0;
        }

        ++turn;
    }
}
