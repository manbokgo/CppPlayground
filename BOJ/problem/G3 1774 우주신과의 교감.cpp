// URL: https://www.acmicpc.net/problem/1774
// Algo: MST 크루스칼

// Start:	240709 16 50
// Read:	0 1
// Think:	0 2
// Code:	0 34 int 쓰면 오버플로 난다고!!!
// Total:	0 37

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) x.begin(), x.end()
#define pb push_back

using ll = long long;
using pii = pair<int, int>;
using tlii = tuple<ll, int, int>;

int p[1'001];

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

ll GetDist(pii a, pii b)
{
    const ll y = a.first - b.first;
    const ll x = a.second - b.second;
    return y * y + x * x;
}


int main()
{
    fastio;
    memset(p, -1, sizeof(p));

    int n, m;
    cin >> n >> m;

    vector<pii> pos(n);
    vector<tlii> edge; // {비용, a, b}
    edge.reserve(n * n);

    for (auto& [y, x] : pos)
        cin >> y >> x;

    for (int i = 0; i < n; ++i)
        for (int j = i + 1; j < n; ++j)
            edge.pb({GetDist(pos[i], pos[j]), i, j});

    sort(all(edge));

    int count = 0;
    while (m--)
    {
        int a, b;
        cin >> a >> b;
        --a;
        --b;

        if (!Union(a, b)) continue;
        ++count;
    }

    double answer = 0;
    for (const auto [cost, a, b] : edge)
    {
        if (!Union(a, b)) continue;
        ++count;
        answer += sqrt(cost);
        if (count == n - 1) break;
    }

    cout.precision(2);
    cout << fixed << answer;
}
