// URL: https://www.acmicpc.net/problem/16724
// Algo: MST 크루스칼 or DFS

// Start:	240804 20 22
// Read:	0 2
// Think:	0 2
// Code:	0 5
// Total:	0 9

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) x.begin(), x.end()
#define pb push_back

int p[1'000'000];

int Find(int a)
{
    if (p[a] < 0) return a;
    return p[a] = Find(p[a]);
}

bool Union(int a, int b)
{
    int ap = Find(a);
    int bp = Find(b);
    if (ap == bp) return false;

    if (-p[ap] < -p[bp]) swap(ap, bp);
    p[ap] += p[bp];
    p[bp] = ap;
    return true;
}

int main()
{
    fastio;
    memset(p, -1, sizeof(p));

    int n, m;
    cin >> n >> m;
    for (int y = 0; y < n; ++y)
    {
        for (int x = 0; x < m; ++x)
        {
            const int idx = y * m + x;

            char c;
            cin >> c;

            int nIdx = -1;
            if (c == 'U') nIdx = (y - 1) * m + x;
            else if (c == 'D') nIdx = (y + 1) * m + x;
            else if (c == 'L') nIdx = y * m + x - 1;
            else if (c == 'R') nIdx = y * m + x + 1;

            Union(idx, nIdx);
        }
    }

    int answer = 0;
    for (int i = 0; i < n * m; ++i)
    {
        if (p[i] < 0) ++answer;
    }
    cout << answer;
}
