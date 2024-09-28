// URL: https://www.acmicpc.net/problem/1074
// Algo: 분할 정복, 재귀

// Start:	240928 12 57
// Read:	0 1
// Think:	0 3
// Code:	0 11
// Total:	0 15

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) x.begin(), x.end()
#define pb push_back

int n;
int r, c;
int answer = 0;

void Solve(int y, int x, int sz)
{
    if (y == r && x == c)
    {
        cout << answer;
        exit(0);
    }

    if (r >= y + sz || r < y || c >= x + sz || c < x)
    {
        answer += sz * sz;
        return;
    }

    Solve(y, x, sz / 2);
    Solve(y, x + sz / 2, sz / 2);
    Solve(y + sz / 2, x, sz / 2);
    Solve(y + sz / 2, x + sz / 2, sz / 2);
}


int main()
{
    fastio;

    cin >> n >> r >> c;
    Solve(0, 0, 1 << n);
}
