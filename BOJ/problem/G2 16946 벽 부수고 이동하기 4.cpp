// URL: https://www.acmicpc.net/problem/16946
// Algo: BFS

// Start:	240917 08 54
// Read:	0 1
// Think:	0 1
// Code:	0 21
// Total:	0 23

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) x.begin(), x.end()
#define pb push_back

using pii = pair<int, int>;

constexpr int INF = 0x3f3f3f3f;

int n, m;
int dy[4] = {0, 1, 0, -1};
int dx[4] = {1, 0, -1, 0}; // 동남서북
inline bool OOB(int y, int x) { return y < 0 || y >= n || x < 0 || x >= m; }

int board[1'000][1'000];
int group[1'000][1'000];

void BFS(int sy, int sx)
{
    static int groupNum = 0;

    queue<pii> q;
    vector<pii> vList;

    board[sy][sx] = 0;
    q.push({sy, sx});
    vList.pb({sy, sx});

    while (!q.empty())
    {
        const auto [cy, cx] = q.front();
        q.pop();

        for (int i = 0; i < 4; ++i)
        {
            const int ny = cy + dy[i];
            const int nx = cx + dx[i];
            if (OOB(ny, nx) || board[ny][nx] != -1) continue;
            board[ny][nx] = 0;
            q.push({ny, nx});
            vList.pb({ny, nx});
        }
    }

    for (const auto& [y, x] : vList)
    {
        board[y][x] = vList.size();
        group[y][x] = groupNum;
    }
    ++groupNum;
}


int main()
{
    fastio;

    cin >> n >> m;
    for (int y = 0; y < n; ++y)
    {
        for (int x = 0; x < m; ++x)
        {
            char num;
            cin >> num;
            if (num == '1') board[y][x] = INF;
            else board[y][x] = -1;
        }
    }

    for (int y = 0; y < n; ++y)
    {
        for (int x = 0; x < m; ++x)
        {
            if (board[y][x] == -1) BFS(y, x);
        }
    }

    for (int y = 0; y < n; ++y)
    {
        for (int x = 0; x < m; ++x)
        {
            if (board[y][x] != INF)
            {
                cout << 0;
                continue;
            }

            set<int> visitedGroup;

            int cnt = 1;
            for (int i = 0; i < 4; ++i)
            {
                const int ny = y + dy[i];
                const int nx = x + dx[i];
                if (OOB(ny, nx) || board[ny][nx] == INF) continue;
                if (visitedGroup.count(group[ny][nx])) continue;

                cnt += board[ny][nx];
                visitedGroup.insert(group[ny][nx]);
            }
            cout << cnt % 10;
        }
        cout << '\n';
    }
}
