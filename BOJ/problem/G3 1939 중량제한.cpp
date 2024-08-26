// URL: https://www.acmicpc.net/problem/1939
// Algo: MST 크루스칼 변형 or 다익스트라 변형 or 이분탐색, BFS

// Start:	240826 13 09
// Read:	0 1
// Think:	0 2
// Code:	0 5
// Total:	0 8

// G4 13905와 동일한 최대 스패닝 트리 문제.
// 마찬가지로 다익스트라 변형으로도 풀 수 있고, 이분 탐색으로 이동량 값을 정한 후 BFS를 돌리면서
// 가능한 이동량의 최대값을 구할 수도 있다.

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) x.begin(), x.end()
#define pb push_back

constexpr int INF = 0x3f3f3f3f;
using tiii = tuple<int, int, int>;

// MST 크루스칼 변형
int p[10'001];
tiii edge[100'000];

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

    int n, m, s, e;
    cin >> n >> m;
    for (int i = 0; i < m; ++i)
    {
        auto& [c, a, b] = edge[i];
        cin >> a >> b >> c;
    }
    cin >> s >> e;

    sort(edge, edge + m, greater<>());

    int cnt = 0;
    int answer = INF;
    for (int i = 0; i < m; ++i)
    {
        auto [cost, a, b] = edge[i];
        if (!Union(a, b)) continue;

        answer = min(answer, cost);
        if (Find(s) == Find(e)) break;

        ++cnt;
        if (cnt == n - 1) break;
    }

    cout << answer;
}