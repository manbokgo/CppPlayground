// URL: https://www.acmicpc.net/problem/20058
// Algo: 시뮬레이션, BFS

// Start:	241010 00 54
// Read:	0 5
// Think:	0 4
// Code:	0 36
// Total:	0 45

// 굉장히 귀찮은 문제였다.

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) x.begin(), x.end()
#define pb push_back

using pii = pair<int, int>;

int n, T;
int dy[4] = {0, 1, 0, -1};
int dx[4] = {1, 0, -1, 0}; // 동남서북
bool OOB(int y, int x) { return y < 0 || y >= n || x < 0 || x >= n; }

int board[64][64];
int preBoard[64][64];
bool visited[64][64];

void Rotate(int startY, int startX, int sz)
{
    for (int fy = startY, tx = startX + sz - 1;
         fy < startY + sz;
         ++fy, --tx)
    {
        for (int fx = startX, ty = startY;
             fx < startX + sz;
             ++fx, ++ty)
        {
            preBoard[ty][tx] = board[fy][fx];
        }
    }
}

int main()
{
    fastio;
    cin >> n >> T;
    n = 1 << n;

    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            cin >> board[i][j];
        }
    }

    while (T--)
    {
        int L;
        cin >> L;
        L = 1 << L;

        for (int y = 0; y < n; y += L)
        {
            for (int x = 0; x < n; x += L)
            {
                Rotate(y, x, L);
            }
        }

        for (int y = 0; y < n; ++y)
        {
            for (int x = 0; x < n; ++x)
            {
                board[y][x] = preBoard[y][x];
                if (preBoard[y][x] == 0) continue;

                int cnt = 0;
                for (int i = 0; i < 4; ++i)
                {
                    const int ny = y + dy[i];
                    const int nx = x + dx[i];
                    if (OOB(ny, nx) || preBoard[ny][nx] == 0) continue;
                    ++cnt;
                }
                if (cnt < 3) --board[y][x];
            }
        }
    }

    int sum = 0;
    for (int y = 0; y < n; ++y)
    {
        for (int x = 0; x < n; ++x)
        {
            sum += board[y][x];
        }
    }
    cout << sum << '\n';

    int mxSz = 0;
    for (int y = 0; y < n; ++y)
    {
        for (int x = 0; x < n; ++x)
        {
            if (board[y][x] == 0 || visited[y][x]) continue;

            queue<pii> q;
            visited[y][x] = true;
            q.push({y, x});

            int cnt = 0;
            while (!q.empty())
            {
                const auto [cy, cx] = q.front();
                q.pop();

                ++cnt;
                for (int i = 0; i < 4; ++i)
                {
                    const int ny = cy + dy[i];
                    const int nx = cx + dx[i];
                    if (OOB(ny, nx) || board[ny][nx] == 0 || visited[ny][nx]) continue;
                    visited[ny][nx] = true;
                    q.push({ny, nx});
                }
            }

            mxSz = max(mxSz, cnt);
        }
    }
    cout << mxSz;
}
