// URL: https://www.acmicpc.net/problem/1647
// Algo: MST 크루스칼

// Start:	240218 02 22
// Read:	0 1
// Think:	0 2
// Code:	0 10
// Total:	0 13

#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define X first
#define Y second
#define all(x) x.begin(), x.end()
#define sortvec(x) sort(all(x))
#define compress(x) x.erase(unique(all(x)), x.end())
#define findvec(x, value) find(all(x), value) != x.end()

using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;

constexpr ll  MOD = 1000000007;
constexpr int INF = 0x3f3f3f3f;
constexpr ll  LLINF = 1e18;

tuple<int, int, int> edge[1'000'005];
int                  p[100'005];

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
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    memset(p, -1, sizeof(p));

    int N, M;
    cin >> N >> M;

    for (int i = 0; i < M; ++i)
    {
        int a, b, c;
        cin >> a >> b >> c;

        edge[i] = {c, a, b};
    }

    sort(edge, edge + M);

    int count = 0;
    int answer = 0;
    int maxCost = 0;

    for (int i = 0; i < M; ++i)
    {
        auto [cost, a, b] = edge[i];
        if (!Union(a, b)) continue;
        ++count;
        maxCost = cost; // 나중에 확정될수록 비용 높은 간선이라 max(maxCost, cost) 필요 없음
        answer += cost;

        if (count == N - 1) break;

        // 어차피 마지막에 확정되는 간선이 제일 비용 높은 것이니 maxCost 변수 없애고 N-2에서 중단해도 됨
        // if (count == N - 2) break;
        // 그런데 이러면 N이 2일 때 멈추지 않고 계속 진행하니 (>= 조건으로 해도 answer가 불필요하게 더해져서 틀린다)
        // MST 만들 필요 없이 if (N == 2) { cout << "0"; return 0; } 로
        // 바로 프로그램을 종료시켜야함. 너무 번잡스러운 듯. 쓸데없는 최적화하지 말자.
    }

    cout << answer - maxCost;
}
