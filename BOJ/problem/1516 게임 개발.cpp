// URL: https://www.acmicpc.net/problem/1516
// Algo: 위상 정렬, DP

// Start:	240227 19 56
// Read:	0 0
// Think:	0 1
// Code:	0 18
// Total:	0 19

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
using tlll = tuple<ll, ll, ll>;

constexpr int INF = 0x3f3f3f3f;
// constexpr ll  LLINF = 1e18;
// constexpr ll  MOD = 1000000007;

// int dy[4] = {0, 1, 0, -1};
// int dx[4] = {1, 0, -1, 0}; // 동남서북
// bool OOB(int y, int x) { return y < 0 || y >= n || x < 0 || x >= m; }

vector<int> adj[505];
int         indegree[505];
int         cost[505];
int         dp[505];

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    int start = 1;
    for (int i = 1; i <= n; ++i)
    {
        cin >> cost[i];
        while (true)
        {
            int edge;
            cin >> edge;
            if (edge == -1) break;
            adj[edge].pb(i);
            ++indegree[i];
        }
    }

    queue<int> q;
    for (int i = 1; i <= n; ++i)
    {
        if (indegree[i] == 0)
        {
            q.push(i);
            dp[i] = cost[i];
        }
    }

    while (!q.empty())
    {
        int cur = q.front();
        q.pop();

        for (auto nxt : adj[cur])
        {
            dp[nxt] = max(dp[nxt], dp[cur] + cost[nxt]);
            --indegree[nxt];
            if (indegree[nxt] == 0)
            {
                q.push(nxt);
            }
        }
    }

    // 사이클 검출 생략

    for (int i = 1; i <= n; ++i)
    {
        cout << dp[i] << "\n";
    }
}
