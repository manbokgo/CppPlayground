// URL: https://www.acmicpc.net/problem/13308
// Algo: 다익스트라 변형, DP

// Start:	240801 07 27
// Read:	0 3
// Think:	0 18
// Code:	0 22
// Total:   0 43
// 오모시로이

// 한 정점에서 출발하는 최단 경로를 찾으니 다익스트라임.
// 예제1이 굉장히 큰 힌트였다. 1-3-4 순으로 바로 가는 루트와, 1-2-1-3-4로 2를 찍고 다시 1로 온 후 진행하는 루트 중 후자가 최소 비용인데,
// 전자와 같이 1 위치지만, 비용 cost가 14에 쭉 2원으로 연료를 채울 수 있다는 게 차이점임.

// 동일한 위치더라도 다른 상황이 발생하며, 연료값이 더 낮은 노드를 밟은 후 쭉 영향을 끼치므로
// D 배열에 '연료값' 차원을 하나 더 추가하여, 전자는 D[1][5] = 0, 후자는 D[1][2] = 14 로 표기할 수 있음

// 우선순위 큐에 넣을 때,  cost + 간선 길이 * 현재까지의 연료값  이 D[다음노드][다음노드에서부터의 연료값] 에 대응한다는
// 약간 까다로운 부분을 유의해야 함. 1-2 갈 때  0 + 2 * 5 가 D[2][2] 에 들어가게 된다.

// D 배열과 cost 변수는 ll 타입이어야 한다. 2500 연료값으로 2500거리 가는 걸, 최소 2500 간선 이상씩 반복하는데
// 그러면 누적값은 150억이 훌쩍 넘음.

// + 따지고 보니 좀 더 효율적인 방법이 있다. 위 방법의 경우 D[1][2]가 14로 이미 확정된 이후, D[1][4]가 27로 진입해서
// 쓸데없이 탐색하게 된다. 더 느리게 1번 노드에 도착하는데, 연료값 또한 더 비싸다면 아무짝에 쓸모가 없다.
// 먼저 큐에서 꺼내져 확정된 것이 가장 비용이 작고, 그 이후부턴 오직 연료가 더 적은 것만 의미있다는 점을 이용해 최적화한다.

// 확정할 때 어느 연료값으로 확정되었는지를 따로 저장한다.
// 다음에 큐에서 꺼낸 것이 이미 확정된 값보다 크다면 쓸모 없으니 스킵하고, 작다면 갱신한다.

// 서브태스크 1~4는 메모리가 1/25 수준으로 확 감소하며 0ms가 되었고,
// 서브태스크 5는 메모리 1/4배로 줄었지만 시간은 거의 비슷하다. 음... 어차피 통과인데 굳이 어렵게 생각하지 말자

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) x.begin(), x.end()
#define pb push_back

constexpr int INF = 0x3f3f3f3f;

using ll = long long;
using pii = pair<int, int>;
using tlii = tuple<ll, int, int>;


int n, m;
int P[2'501];
vector<pii> adj[2'501];


// 최적화 풀이. 292ms 27MB
ll D[2'501];
ll mxFuel[2'501];

int main()
{
    fastio;
    memset(D, INF, sizeof(D));
    memset(mxFuel, INF, sizeof(mxFuel));

    cin >> n >> m;
    for (int i = 1; i <= n; ++i)
        cin >> P[i];

    while (m--)
    {
        int a, b, c;
        cin >> a >> b >> c;
        adj[a].pb({c, b});
        adj[b].pb({c, a});
    }

    priority_queue<tlii, vector<tlii>, greater<>> pq;
    D[1] = 0;
    pq.push({D[1], 1, P[1]});

    while (!pq.empty())
    {
        const auto [cost, node, curPrice] = pq.top();
        pq.pop();

        if (node == n)
        {
            cout << cost;
            return 0;
        }

        if (mxFuel[node] <= curPrice) continue;
        mxFuel[node] = curPrice;

        for (const auto [nCost, nNode] : adj[node])
        {
            const int nPrice = min(curPrice, P[nNode]);
            if (mxFuel[nNode] <= nPrice) continue;
            D[nNode] = cost + nCost * curPrice;
            pq.push({D[nNode], nNode, nPrice});
        }
    }
}

// 첫 풀이. 328ms 100MB
/*
vector<pii> adj[2'501];
ll D[2'501][2'501]; // 도시, 최소 연료값

int main()
{
    fastio;
    memset(D, INF, sizeof(D));

    cin >> n >> m;
    for (int i = 1; i <= n; ++i)
        cin >> P[i];

    while (m--)
    {
        int a, b, c;
        cin >> a >> b >> c;
        adj[a].pb({c, b});
        adj[b].pb({c, a});
    }

    priority_queue<tlii, vector<tlii>, greater<>> pq;
    D[1][P[1]] = 0;
    pq.push({D[1][P[1]], 1, P[1]});

    while (!pq.empty())
    {
        const auto [cost, node, curPrice] = pq.top();
        pq.pop();

        if (node == n)
        {
            cout << cost;
            return 0;
        }

        if (D[node][curPrice] != cost) continue;
        for (const auto [nCost, nNode] : adj[node])
        {
            const int nPrice = min(curPrice, P[nNode]);
            if (D[nNode][nPrice] <= cost + nCost * curPrice) continue;
            D[nNode][nPrice] = cost + nCost * curPrice;
            pq.push({D[nNode][nPrice], nNode, nPrice});
        }
    }
}
*/