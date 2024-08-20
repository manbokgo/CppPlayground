// URL: https://www.acmicpc.net/problem/1486
// Algo: 다익스트라 All to One or 플로이드

// Start:	240820 01 53
// Read:	0 3
// Think:	0 3
// Code:	0 30
// Total:	0 36

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) x.begin(), x.end()
#define pb push_back

constexpr int INF = 0x3f3f3f3f;
using tiii = tuple<int, int, int>;

int n, m, t, d;
char board[25][25];
int D[25][25];
int Dback[25][25];

int dy[4] = {0, 1, 0, -1};
int dx[4] = {1, 0, -1, 0}; // 동남서북
bool OOB(int y, int x) { return y < 0 || y >= n || x < 0 || x >= m; }

int main()
{
    fastio;
    memset(D, INF, sizeof(D));
    memset(Dback, INF, sizeof(Dback));

    cin >> n >> m >> t >> d;
    for (int y = 0; y < n; ++y)
    {
        for (int x = 0; x < m; ++x)
        {
            cin >> board[y][x];
            if (board[y][x] - 'a' < 0)
            {
                board[y][x] -= 'A';
            }
            else
            {
                board[y][x] -= 'a';
                board[y][x] += 26;
            }
        }
    }

    {
        priority_queue<tiii, vector<tiii>, greater<>> pq;
        D[0][0] = 0;
        pq.push({D[0][0], 0, 0});

        while (!pq.empty())
        {
            const auto [dist, cy, cx] = pq.top();
            pq.pop();
            if (dist != D[cy][cx]) continue;

            for (int i = 0; i < 4; ++i)
            {
                const int ny = cy + dy[i];
                const int nx = cx + dx[i];
                if (OOB(ny, nx)) continue;

                const int diff = board[ny][nx] - board[cy][cx];
                if (abs(diff) > t) continue;

                int nDist = dist;
                if (diff > 0) nDist += diff * diff;
                else nDist += 1;

                if (D[ny][nx] <= nDist) continue;
                D[ny][nx] = nDist;
                pq.push({D[ny][nx], ny, nx});
            }
        }
    }

    // 역간선 All to One
    {
        priority_queue<tiii, vector<tiii>, greater<>> pq;
        Dback[0][0] = 0;
        pq.push({Dback[0][0], 0, 0});

        while (!pq.empty())
        {
            const auto [dist, cy, cx] = pq.top();
            pq.pop();
            if (dist != Dback[cy][cx]) continue;

            for (int i = 0; i < 4; ++i)
            {
                const int ny = cy + dy[i];
                const int nx = cx + dx[i];
                if (OOB(ny, nx)) continue;

                const int diff = board[ny][nx] - board[cy][cx];
                if (abs(diff) > t) continue;

                int nDist = dist;
                if (diff < 0) nDist += diff * diff;
                else nDist += 1;

                if (Dback[ny][nx] <= nDist) continue;
                Dback[ny][nx] = nDist;
                pq.push({Dback[ny][nx], ny, nx});
            }
        }
    }

    int answer = -1;
    for (int y = 0; y < n; ++y)
    {
        for (int x = 0; x < m; ++x)
        {
            if (D[y][x] + Dback[y][x] > d) continue;
            answer = max(answer, (int)board[y][x]);
        }
    }
    cout << answer;
}
