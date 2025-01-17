// URL: https://www.acmicpc.net/problem/2448
// Algo: 재귀

// Start:	250118 07 04
// Read:	
// Think:	
// Code:	
// Total:	

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) x.begin(), x.end()
#define pb push_back

char board[3072][6144];

void Star(int y, int x, int n)
{
    if (n == 3)
    {
        board[y][x] = '*';

        board[y + 1][x - 1] = '*';
        board[y + 1][x + 1] = '*';

        board[y + 2][x - 2] = '*';
        board[y + 2][x - 1] = '*';
        board[y + 2][x + 0] = '*';
        board[y + 2][x + 1] = '*';
        board[y + 2][x + 2] = '*';
    }
    else
    {
        Star(y, x, n / 2);
        Star(y + n / 2, x - n / 2, n / 2);
        Star(y + n / 2, x + n / 2, n / 2);
    }
}


int main()
{
    fastio;
    memset(board, ' ', sizeof(board));

    int n;
    cin >> n;
    Star(0, n - 1, n);

    for (int y = 0; y < n; ++y)
    {
        for (int x = 0; x < 2 * n - 1; ++x)
        {
            cout << board[y][x];
        }
        cout << '\n';
    }
}
