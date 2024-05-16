// URL: https://www.acmicpc.net/problem/17780
// Algo: 시뮬레이션

// Start:	240516 13 00
// Read:	0 3
// Think:	0 3
// Code:	0 23
// Total:	0 29

// 함정이랄 것도 없이 문제에 나온대로 그대로 구현하면 된다.
// 이런게 왜 골2?

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
struct pieceInfo
{
    int y;
    int x;
    int dir;
};

struct tile
{
    // 0 흰색, 1 빨간색, 2 파란색
    int color;
    vector<int> lst;
};

int n, k;
tile tiles[13][13];   // 칸, 말목록
pieceInfo pieces[11]; // y, x, 방향

int dy[4] = {0, 0, -1, 1};
int dx[4] = {1, -1, 0, 0}; // 동서북남
bool OOB(int y, int x) { return y <= 0 || y > n || x <= 0 || x > n; }

int RevDir(int dir)
{
    if (dir % 2 == 0) return dir + 1;
    else return dir - 1;
}

int main()
{
    fastio;
    cin >> n >> k;

    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
            cin >> tiles[i][j].color;

    for (int i = 1; i <= k; ++i)
    {
        int a, b, c;
        cin >> a >> b >> c;

        pieces[i] = {a, b, c-1};
        tiles[a][b].lst.push_back(i);
        if (tiles[a][b].lst.size() >= 4)
        {
            cout << 0;
            return 0;
        }
    }

    for (int turn = 1; turn <= 1000; ++turn)
    {
        for (int pIdx = 1; pIdx <= k; ++pIdx)
        {
            auto& [y, x, dir] = pieces[pIdx];
            auto& [color, lst] = tiles[y][x];
            if (lst.front() != pIdx) continue;

            int ny = y + dy[dir];
            int nx = x + dx[dir];
            if (OOB(ny, nx) || tiles[ny][nx].color == 2)
            {
                dir = RevDir(dir);
                ny = y + dy[dir];
                nx = x + dx[dir];
                if (OOB(ny, nx) || tiles[ny][nx].color == 2) continue;
            }

            auto& [nColor, nLst] = tiles[ny][nx];
            if (nColor == 0)
                nLst.insert(nLst.end(), lst.begin(), lst.end());
            else if (nColor == 1)
                nLst.insert(nLst.end(), lst.rbegin(), lst.rend());

            for (const int piece : lst)
            {
                pieces[piece].y = ny;
                pieces[piece].x = nx;
            }
            lst.clear();
            if (nLst.size() >= 4)
            {
                cout << turn;
                return 0;
            }
        }
    }

    cout << -1;
    return 0;
}
