// URL: https://www.acmicpc.net/problem/1197
// Algo: MST 크루스칼

// Start:	240524 23 16
// Read:	0 1
// Think:	0 1
// Code:	0 3
// Total:	0 5

// 크루스칼, 유니온 파인드는 이제 눈 (반쯤만) 감고도 치겠다

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
using tiii = tuple<int, int, int>;

int p[10'001];
tiii edge[100'001];

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

    if (p[ap] > p[bp]) swap(ap, bp);
    p[ap] += p[bp];
    p[bp] = ap;
    return true;
}

int main()
{
    fastio;
    memset(p, -1, sizeof(p));

    int V, E;
    cin >> V >> E;

    for (int i = 0; i < E; ++i)
    {
        auto& [c, a, b] = edge[i];
        cin >> a >> b >> c;
    }
    sort(edge, edge + E);

    int answer = 0;
    int cnt = 0;
    for (const auto& [c, a, b] : edge)
    {
        if (!Union(a, b)) continue;
        ++cnt;
        answer += c;
        if (cnt == V-1) break;
    }

    cout << answer;
}
