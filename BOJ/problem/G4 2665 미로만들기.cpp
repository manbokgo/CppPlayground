// URL: https://www.acmicpc.net/problem/2665
// Algo: 0-1 BFS 기본 or 다익스트라

// Start:	240930 14 41
// Read:	0 1
// Think:	0 2
// Code:	0 5
// Total:	0 8

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) x.begin(), x.end()
#define pb push_back

using pii = pair<int, int>;

constexpr int INF = 0x3f3f3f3f;

int n;
int D[50][50];
int cost[50][50];

int dy[4] = {0, 1, 0, -1};
int dx[4] = {1, 0, -1, 0}; // 동남서북
bool OOB(int y, int x) { return y < 0 || y >= n || x < 0 || x >= n; }

int main()
{
    fastio;
    memset(D, INF, sizeof(D));

    cin >> n;

    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            char c;
            cin >> c;
            if (c == '1') cost[i][j] = 0;
            else cost[i][j] = 1;
        }
    }

    deque<pii> dq;
    D[0][0] = 0;
    dq.push_front({0, 0});

    while (!dq.empty())
    {
        auto [y, x] = dq.front();
        dq.pop_front();

        for (int i = 0; i < 4; ++i)
        {
            int ny = y + dy[i];
            int nx = x + dx[i];
            if (OOB(ny, nx)) continue;

            if (D[ny][nx] <= D[y][x] + cost[ny][nx]) continue;
            D[ny][nx] = D[y][x] + cost[ny][nx];

            if (cost[ny][nx]) dq.push_back({ny, nx});
            else dq.push_front({ny, nx});
        }
    }

    cout << D[n-1][n-1];
}
