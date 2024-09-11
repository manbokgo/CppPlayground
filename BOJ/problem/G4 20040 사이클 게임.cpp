// URL: https://www.acmicpc.net/problem/20040
// Algo: 분리 집합 기본

// Start:	240911 14 07
// Read:	0 1
// Think:	0 1
// Code:	0 6
// Total:	0 8

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) x.begin(), x.end()
#define pb push_back

int p[500'000];

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

    for (int i = 1; i <= m; ++i)
    {
        int a, b;
        cin >> a >> b;
        if (!Union(a, b))
        {
            cout << i;
            return 0;
        }
    }

    cout << 0;
    return 0;
}
