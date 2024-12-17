// URL: https://www.acmicpc.net/problem/10473
// Algo: 다익스트라, 기하학

// Start:	241217 19 20
// Read:	0 2
// Think:	0 8
// Code:	0 25
// Total:	0 35

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) x.begin(), x.end()
#define pb push_back

using pdi = pair<double, int>;
using pdd = pair<double, double>;

pdd pos[102];
double D[102];

int main()
{
    fastio;
    fill_n(D, 102, 1e8);

    cin >> pos[0].first >> pos[0].second
        >> pos[1].first >> pos[1].second;

    int n;
    cin >> n;
    n += 2;

    for (int i = 2; i < n; ++i)
        cin >> pos[i].first >> pos[i].second;

    priority_queue<pdi, vector<pdi>, greater<>> pq;
    D[0] = 0;
    pq.push({D[0], 0});

    while (!pq.empty())
    {
        const auto [dist, node] = pq.top();
        pq.pop();

        if (dist > D[node]) continue;

        const auto [sx, sy] = pos[node];
        for (int nNode = 0; nNode < n; ++nNode)
        {
            if (nNode == node) continue;
            const auto [ex, ey] = pos[nNode];
            const double len = hypot(abs(ex - sx), abs(ey - sy));

            double nDist = len / 5;
            if (node != 0) nDist = min(nDist, 2 + abs(len - 50) / 5);

            if (D[nNode] <= dist + nDist) continue;
            D[nNode] = dist + nDist;
            pq.push({D[nNode], nNode});
        }
    }

    cout << D[1];
}
