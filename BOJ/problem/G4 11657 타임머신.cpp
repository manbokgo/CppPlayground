// URL: https://www.acmicpc.net/problem/11657
// Algo: 벨만 포드 기본

// Start:	240903 16 56
// Read:	0 1
// Think:	0 1
// Code:	0 18
// Total:	0 20

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) x.begin(), x.end()
#define pb push_back

using tiii = tuple<int, int, int>;
using ll = long long;

constexpr int INF = 0x3f3f3f3f;
int n, m;
ll D[501];
tiii edges[6000];

bool Bellman(int st)
{
    D[st] = 0;
    for (int i = 1; i <= n; ++i)
    {
        for (const auto& [a, b, c] : edges)
        {
            if (D[a] == INF) continue;
            if (D[b] <= D[a] + c) continue;
            D[b] = D[a] + c;
            if (i == n) return true; // n회차의 변경은 음수 사이클 존재
        }
    }
    return false;
}

int main()
{
    fastio;
    fill_n(D, 501, INF); // 문제 조건상 ll 배열이라서 int INF를 memset하면 안 된다

    cin >> n >> m;
    for (int i = 0; i < m; ++i)
    {
        auto& [a, b, c] = edges[i];
        cin >> a >> b >> c;
    }

    const bool cycle = Bellman(1);
    if (cycle)
    {
        cout << -1;
        return 0;
    }
        
    for (int i = 2; i <= n; ++i)
    {
        if (D[i] == INF) cout << -1 << '\n';
        else cout << D[i] << '\n';
    }
}
