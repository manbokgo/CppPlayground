// URL: https://www.acmicpc.net/problem/9328
// Algo: 시뮬레이션, BFS

// Start:	240530 18 44
// Read:	0 2
// Think:	0 4
// Code:	0 28    알파벳은 26글자인데 23글자라고 착각함. 후...
// Total:	0 34

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) x.begin(), x.end()
#define pb push_back

using pii = pair<int, int>;

int n, m;
int dy[4] = {0, 1, 0, -1};
int dx[4] = {1, 0, -1, 0}; // 동남서북
bool OOB(int y, int x) { return y < 0 || y >= n || x < 0 || x >= m; }

char board[100][100];
bool visited[100][100];
vector<pii> findDoor[26];
bool keys[26];
int answer = 0;

bool CanGo(int y, int x, queue<pii>* q)
{
    if (OOB(y, x) || visited[y][x]) return false;

    const auto& tile = board[y][x];
    if (tile == '*')
    {
        return false;
    }

    if (tile == '.')
    {
        visited[y][x] = true;
        q->push({y, x});
        return true;
    }

    if (tile == '$')
    {
        visited[y][x] = true;
        q->push({y, x});

        ++answer;
        return true;
    }

    if (const int keyNum = tile - 'a';
        0 <= keyNum && keyNum < 26)
    {
        visited[y][x] = true;
        q->push({y, x});

        if (!keys[keyNum])
        {
            keys[keyNum] = true;
            for (const auto [ty, tx] : findDoor[keyNum])
            {
                visited[ty][tx] = true;
                q->push({ty, tx});
            }
        }

        return true;
    }

    if (const int doorNum = tile - 'A';
        0 <= doorNum && doorNum < 26)
    {
        if (keys[doorNum])
        {
            visited[y][x] = true;
            q->push({y, x});
            return true;
        }
        else
        {
            findDoor[doorNum].pb({y, x});
            return false;
        }
    }

    return false; // dummy
}

int main()
{
    fastio;
    int T;
    cin >> T;

    while (T--)
    {
        memset(visited, false, sizeof(visited));
        for (auto& door : findDoor) door.clear();
        memset(keys, false, sizeof(keys));
        answer = 0;

        cin >> n >> m;
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < m; ++j)
            {
                cin >> board[i][j];
            }
        }

        string haveKey;
        cin >> haveKey;
        if (haveKey != "0")
        {
            for (const char k : haveKey)
            {
                keys[k - 'a'] = true;
            }
        }

        queue<pii> q;
        for (int i = 0; i < n; ++i)
        {
            CanGo(i, 0, &q);
            CanGo(i, m - 1, &q);
        }

        for (int j = 0; j < m; ++j)
        {
            CanGo(0, j, &q);
            CanGo(n - 1, j, &q);
        }

        while (!q.empty())
        {
            const auto [y, x] = q.front();
            q.pop();

            for (int i = 0; i < 4; ++i)
            {
                const int ny = y + dy[i];
                const int nx = x + dx[i];
                CanGo(ny, nx, &q);
            }
        }

        cout << answer << '\n';
    }
}
