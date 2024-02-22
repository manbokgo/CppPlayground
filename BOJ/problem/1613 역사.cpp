// URL: https://www.acmicpc.net/problem/1613
// Algo: 플로이드

// Start:	240222 17 20
// Read:	0 1
// Think:	0 2
// Code:	0 10  플로이드 dist bool 풀이 68ms
// Total:	0 13
// +
// Code:	0 3  플로이드 dist int 풀이. 84ms. 시간 16ms 늘어나지만 원래대로 int 기본형으로 하는게 덜 헷갈리고 좋은 듯

// 위상 정렬은 불가.  1-2  가 있다고 할 때 2, 3끼리는 실제론 순서를 알 수 없지만, 위상 정렬에선 임의로 나열되므로 이런 경우 구분 불가.
//                    \3
// 단방향 그래프 플로이드 돌려서 s에서 e로 진행 가능하면 정시간순이라고 판단해야함 O(V^3)
// 테스트 케이스마다 O(1)으로 판단 가능
//
// 다익스트라 O(E logE)를 t번 반복하는 건 당연히 더 느림. 케이스마다 from->to, to->from 최대 2번 해야하는데
// 거기다 E, t가 V와 비슷한 경우조차 아님. O(2*50,000*50,000*log50,000)
//
// 모든 간선의 비용이 1이고, 플로이드에서 구하는 모든 정점간 '최단' 거리는 불필요한 정보인 문제이므로 DFS(BFS)로도 접근 가능.
// 인접리스트 DFS(BFS)를 플로이드처럼 V번 돌려서 dist 배열을 채우면 O(V^2+VE)로 더 빠름. 32ms.
// 참고 코드: https://www.acmicpc.net/source/41598382


#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define X first
#define Y second
#define all(x) x.begin(), x.end()
#define sortVec(x) sort(all(x))
#define compress(x) x.erase(unique(all(x)), x.end())
#define existInVec(x, value) find(all(x), value) != x.end()

using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using tiii = tuple<int, int, int>;

constexpr ll  MOD = 1000000007;
constexpr int INF = 0x3f3f3f3f;
constexpr ll  LLINF = 1e18;

int dist[405][405];

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    memset(dist, INF, sizeof(dist));

    int n, k;
    cin >> n >> k;

    while (k--)
    {
        int st, en;
        cin >> st >> en;
        dist[st][en] = 1;
    }

    for (int i = 1; i <= n; ++i)
    {
        dist[i][i] = 0;
        for (int s = 1; s <= n; ++s)
        {
            for (int e = 1; e <= n; ++e)
            {
                 dist[s][e] = min(dist[s][e], dist[s][i] + dist[i][e]);
            }
        }
    }

    int t;
    cin >> t;
    while (t--)
    {
        int st, en;
        cin >> st >> en;

        if (dist[st][en] != INF) cout << -1 << "\n";
        else if (dist[en][st] != INF) cout << 1 << "\n";
        else cout << 0 << "\n";
    }
}