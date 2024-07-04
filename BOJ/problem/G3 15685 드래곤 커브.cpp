// URL: https://www.acmicpc.net/problem/15685
// Algo: 시뮬레이션

// Start:	240704 15 04
// Read:	0 3
// Think:	0 5
// Code:	0 6
// Total:	0 14

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) x.begin(), x.end()
#define pb push_back

int dy[4] = {0, -1, 0, 1};
int dx[4] = {1, 0, -1, 0}; // 동북서남
bool OOB(int y, int x) { return y < 0 || y >= 101 || x < 0 || x >= 101; }

bool arr[101][101];

int main()
{
    fastio;

    int n;
    cin >> n;

    while (n--)
    {
        int x, y, d, g;
        cin >> x >> y >> d >> g;

        vector<int> move;
        move.pb(d);

        while (g--)
        {
            for (int i = move.size() - 1; i >= 0; --i)
            {
                move.pb((move[i] + 1) % 4);
            }
        }

        arr[y][x] = true;
        for (const int mv : move)
        {
            y += dy[mv];
            x += dx[mv];
            if (OOB(y, x)) break;
            arr[y][x] = true;
        }
    }

    int answer = 0;
    for (int y = 0; y < 100; ++y)
    {
        for (int x = 0; x < 100; ++x)
        {
            if (arr[y][x] && arr[y][x+1] && arr[y+1][x] && arr[y+1][x+1])
                ++answer;
        }
    }

    cout << answer;
}
