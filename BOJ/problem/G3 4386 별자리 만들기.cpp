// URL: https://www.acmicpc.net/problem/4386
// Algo: MST 크루스칼

// Start:	241102 12 07
// Read:	0 1
// Think:	0 1
// Code:	0 7
// Total:	0 9

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) x.begin(), x.end()
#define pb push_back

using pdd = pair<double, double>;
using tdii = tuple<double, int, int>;

pdd arr[100];
int p[100];
vector<tdii> edges;

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

    int n;
    cin >> n;

    for (int i = 0; i < n; ++i)
    {
        auto& [y, x] = arr[i];
        cin >> y >> x;
    }

    for (int i = 0; i < n; ++i)
    {
        const auto& [y1, x1] = arr[i];
        for (int j = i + 1; j < n; ++j)
        {
            const auto& [y2, x2] = arr[j];
            const double dist = sqrt((y2 - y1) * (y2 - y1) + (x2 - x1) * (x2 - x1));
            edges.pb({dist, i, j});
        }
    }
    sort(all(edges));

    int cnt = 0;
    double answer = 0;

    for (const auto& [cost, a, b] : edges)
    {
        if (!Union(a, b)) continue;
        ++cnt;
        answer += cost;

        if (cnt == n - 1) break;
    }

    cout.precision(2);
    cout << fixed << answer;
}
