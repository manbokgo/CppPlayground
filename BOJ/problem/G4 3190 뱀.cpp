// URL: https://www.acmicpc.net/problem/3190
// Algo: 시뮬레이션

// Start:	250124 18 12
// Read:	0 1
// Think:	0 1
// Code:	0 12
// Total:	0 14

// 마지막 l 이후로 방향을 변경하지 않은 채로 앞으로 계속 나아간다는 점에 유의.

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) x.begin(), x.end()
#define pb push_back

using pii = pair<int, int>;
constexpr int INF = 0x3f3f3f3f;

int n;
int dy[4] = {0, 1, 0, -1};
int dx[4] = {1, 0, -1, 0}; // 동남서북
inline bool OOB(int y, int x) { return y <= 0 || y > n || x <= 0 || x > n; }

bool apple[101][101];
bool visited[101][101];

int main()
{
    fastio;

    int k, l;
    cin >> n >> k;

    while (k--)
    {
        int y, x;
        cin >> y >> x;
        apple[y][x] = true;
    }

    cin >> l;

    queue<pii> q;
    visited[1][1] = true;
    q.push({1, 1});

    int cnt = 0;
    int dir = 0;
    while (true)
    {
        int t = INF;
        char c = '.';
        if (l--) cin >> t >> c;

        while (cnt < t)
        {
            cnt++;
            const auto [cy, cx] = q.back();
            const int ny = cy + dy[dir];
            const int nx = cx + dx[dir];
            if (OOB(ny, nx) || visited[ny][nx])
            {
                cout << cnt;
                return 0;
            }

            visited[ny][nx] = true;
            q.push({ny, nx});

            if (apple[ny][nx])
            {
                apple[ny][nx] = false;
            }
            else
            {
                const auto [fy, fx] = q.front();
                q.pop();
                visited[fy][fx] = false;
            }
        }

        dir = (c == 'L' ? (dir + 3) % 4 : (dir + 1) % 4);
    }
}
