// URL: https://www.acmicpc.net/problem/1915
// Algo: DP

// Start:	240813 08 34
// Read:	0 1
// Think:	0 3
// Code:	0 9
// Total:	0 13

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) x.begin(), x.end()
#define pb push_back

int board[1001][1001];

int main()
{
    fastio;
    int n, m;
    cin >> n >> m;

    int answer = 0;
    for (int y = 1; y <= n; ++y)
    {
        for (int x = 1; x <= m; ++x)
        {
            char c;
            cin >> c;
            c -= '0';
            if (c)
            {
                board[y][x] = min({board[y - 1][x - 1], board[y - 1][x], board[y][x - 1]}) + 1;
                answer = max(answer, board[y][x]);
            }
            else
            {
                board[y][x] = 0;
            }
        }
    }
    cout << answer * answer;
}
