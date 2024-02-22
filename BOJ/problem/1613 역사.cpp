// URL: https://www.acmicpc.net/problem/1613
// Algo: 플로이드

// Start:	240222 17 20
// Read:	0 1
// Think:	0 2
// Code:	0 10  플로이드 dist bool 풀이
// Total:	0 13
// +
// Code:	0 3  플로이드 dist int 풀이. 시간 16ms 늘어나지만 원래대로 int 기본형으로 하는게 덜 헷갈리고 좋은 듯

// 위상 정렬은 불가.  1-2  가 있다고 할 때 2, 3끼리는 실제론 순서를 알 수 없지만, 위상 정렬에선 임의로 나열되므로 이런 경우 구분 불가.
//                    \3
// 단방향 그래프 플로이드 돌려서 s에서 e로 진행 가능하면 정시간순이라고 판단해야함
//
// 다익스트라 O(E logE)를 t번 반복하는게 더 느리다.
// V는 최대 400, E 최대 50,000, t 최대 50,000인데
// 플로이드는 O(400 x 160,000) 이지만 다익스트라 t번은 O(50,000 x 780,482)
// 다익스트라는 E와 t가 V에 비슷한, V^2보다 많이 작은 경우에만 더 효율적임
// 이번 문제처럼(그리고 일반적으로) 그렇지 않다면 모든 정점 간 거리는 플로이드가 더 나음


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