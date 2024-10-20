// URL: https://www.acmicpc.net/problem/4056
// Algo: 백트래킹

// Start:	241020 10 20
// Read:	0 1
// Think:	0 1
// Code:	0 5
// Total:	0 7

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);

int tile[9][9];
bool row[9][10];
bool col[9][10];
bool sqa[9][10];

int GetSqa(int y, int x) { return y / 3 * 3 + x / 3; }

bool DFS(int idx)
{
    if (idx == 81) return true;

    const int y = idx / 9;
    const int x = idx % 9;
    if (tile[y][x] != 0) return DFS(idx + 1);

    const int sq = GetSqa(y, x);
    for (int i = 1; i <= 9; ++i)
    {
        if (row[y][i] || col[x][i] || sqa[sq][i]) continue;

        tile[y][x] = i;
        row[y][i] = col[x][i] = sqa[sq][i] = true;

        if (DFS(idx + 1)) return true;

        tile[y][x] = 0;
        row[y][i] = col[x][i] = sqa[sq][i] = false;
    }

    return false;
}

int main()
{
    fastio;

    int T;
    cin >> T;

    while (T--)
    {
        cout << '\n';
        memset(row, false, sizeof(row));
        memset(col, false, sizeof(col));
        memset(sqa, false, sizeof(sqa));

        for (int i = 0; i < 9; ++i)
        {
            for (int j = 0; j < 9; ++j)
            {
                char c;
                cin >> c;

                const int num = c - '0';
                tile[i][j] = num;
                row[i][num] = true;
                col[j][num] = true;
                sqa[GetSqa(i, j)][num] = true;
            }
        }

        bool bFind = DFS(0);
        if (!bFind)
        {
            cout << "Could not complete this grid.\n";
            continue;
        }

        for (int i = 0; i < 9; ++i)
        {
            for (int j = 0; j < 9; ++j)
            {
                cout << tile[i][j];
            }
            cout << '\n';
        }
    }
}
