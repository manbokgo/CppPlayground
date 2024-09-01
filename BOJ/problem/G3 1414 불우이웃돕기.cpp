// URL: https://www.acmicpc.net/problem/1414
// Algo: MST 크루스칼

// Start:	240901 18 13
// Read:	0 2
// Think:	0 1
// Code:	0 10
// Total:	0 12

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) x.begin(), x.end()
#define pb push_back

using tiii = tuple<int, int, int>;
int n;
int p[50];
vector<tiii> edges;


int Find(int a)
{
    if (p[a] < 0) return a;
    p[a] = Find(p[a]);
    return p[a];
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

    cin >> n;
    edges.reserve(n * n);

    int sum = 0;
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            char c;
            cin >> c;
            if (c == '0') continue;

            if ('a' <= c && c <= 'z') c = c - 'a' + 1;
            else if ('A' <= c && c <= 'Z') c = c - 'A' + 27;

            sum += c;
            edges.pb({c, i, j});
        }
    }
    sort(all(edges));

    int cnt = 0;
    for (const auto [cost, a, b] : edges)
    {
        if (!Union(a, b)) continue;
        ++cnt;
        sum -= cost;

        if (cnt == n - 1) break;
    }

    if (cnt != n - 1) cout << -1;
    else cout << sum;
}
