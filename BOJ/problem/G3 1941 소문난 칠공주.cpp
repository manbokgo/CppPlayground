// URL: https://www.acmicpc.net/problem/1941
// Algo: 브루트포스, 조합, BFS

// Start:	240806 09 05
// Read:	0 2
// Think:	0 8
// Code:	0 13
// Total:	0 23

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) x.begin(), x.end()
#define pb push_back

using pii = pair<int, int>;

int dy[4] = {0, 1, 0, -1};
int dx[4] = {1, 0, -1, 0}; // 동남서북
bool OOB(int y, int x) { return y < 0 || y >= 5 || x < 0 || x >= 5; }

char board[5][5];
bool visited[5][5];

int main()
{
    fastio;
    for (int y = 0; y < 5; ++y)
    {
        for (int x = 0; x < 5; ++x)
        {
            cin >> board[y][x];
        }
    }

    int answer = 0;
    vector<bool> comb(25);
    for (int i = 0; i < 7; ++i) comb[i] = true;
    do
    {
        int sCnt = 0;
        int sIdx = -1;
        for (int i = 0; i < comb.size(); ++i)
        {
            if (!comb[i]) continue;
            const int y = i / 5;
            const int x = i % 5;
            if (board[y][x] == 'S')
            {
                ++sCnt;
                sIdx = i;
            }
        }
        if (sCnt < 4) continue;

        memset(visited, false, sizeof(visited));

        queue<pii> q;
        visited[sIdx / 5][sIdx % 5] = true;
        q.push({sIdx / 5, sIdx % 5});

        int checked = 0;
        while (!q.empty())
        {
            const auto [y, x] = q.front();
            q.pop();
            ++checked;

            for (int i = 0; i < 4; ++i)
            {
                const int ny = y + dy[i];
                const int nx = x + dx[i];
                if (OOB(ny, nx) || !comb[ny * 5 + nx] || visited[ny][nx]) continue;

                visited[ny][nx] = true;
                q.push({ny, nx});
            }
        }

        if (checked == 7) ++answer;
    }
    while (prev_permutation(all(comb)));

    cout << answer;
}
