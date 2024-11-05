// URL: https://www.acmicpc.net/problem/10216
// Algo: 분리 집합, 기하학

// Start:	241105 14 01
// Read:	0 1
// Think:	0 2
// Code:	0 7
// Total:	0 10

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) x.begin(), x.end()
#define pb push_back

using tiii = tuple<int, int, int>;

int p[3'000];
tiii pos[3'000];

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

bool CircleIntersect(int x1, int y1, int r1, int x2, int y2, int r2)
{
    const int distSq = (y2 - y1) * (y2 - y1) + (x2 - x1) * (x2 - x1);
    return distSq <= (r1 + r2) * (r1 + r2);
}

int main()
{
    fastio;

    int T;
    cin >> T;

    while (T--)
    {
        memset(p, -1, sizeof(p));

        int n;
        cin >> n;

        for (int i = 0; i < n; ++i)
        {
            auto& [x, y, r] = pos[i];
            cin >> x >> y >> r;
        }

        for (int i = 0; i < n; ++i)
        {
            const auto [x1, y1, r1] = pos[i];
            for (int j = i + 1; j < n; ++j)
            {
                if (Find(i) == Find(j)) continue;

                const auto [x2, y2, r2] = pos[j];
                if (CircleIntersect(x1, y1, r1, x2, y2, r2))
                {
                    Union(i, j);
                }
            }
        }

        int cnt = 0;
        for (int i = 0; i < n; ++i)
        {
            if (p[i] < 0) ++cnt;
        }
        cout << cnt << '\n';
    }
}
