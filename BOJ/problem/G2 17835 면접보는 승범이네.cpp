// URL: https://www.acmicpc.net/problem/17835
// Algo: 다익스트라

// Start:	240927 20 24
// Read:	0 1
// Think:	0 1
// Code:	0 21
// Total:	0 23

// k번 다익스트라를 돌리는 게 아니라, k를 모두 pq에 넣고 다익스트라를 1번 돌린다.
// 문제 조건상 D의 최대값은 10만x10만 = 100억으로, D는 ll을 사용해야 한다. 쓸데없이 헤맸다..

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) x.begin(), x.end()
#define pb push_back

using ll = long long;
constexpr ll LLINF = 1e18;

using pll = pair<ll, ll>;

ll D[100'001];
vector<pll> adjR[100'001];

int main()
{
    fill_n(D, 100'001, LLINF);

    fastio;
    int n, m, k;
    cin >> n >> m >> k;

    while (m--)
    {
        int a, b, c;
        cin >> a >> b >> c;
        adjR[b].pb({c, a});
    }


    priority_queue<pll, vector<pll>, greater<>> pq;
    while (k--)
    {
        int st;
        cin >> st;
        D[st] = 0;
        pq.push({D[st], st});
    }

    while (!pq.empty())
    {
        const auto [dist, node] = pq.top();
        pq.pop();
        if (dist != D[node]) continue;

        for (const auto& [nDist, nNode] : adjR[node])
        {
            if (D[nNode] <= dist + nDist) continue;;
            D[nNode] = dist + nDist;
            pq.push({D[nNode], nNode});
        }
    }

    ll mxIdx = -1;
    ll mxDist = -1;
    for (int i = 1; i <= n; ++i)
    {
        if (mxDist < D[i])
        {
            mxIdx = i;
            mxDist = D[i];
        }
    }

    cout << mxIdx << '\n' << mxDist;
}
