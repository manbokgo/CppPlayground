// URL: https://www.acmicpc.net/problem/16940
// Algo: BFS 변형

// Start:	240321 20 15
// Read:	0 0
// Think:	0 1
// Code:	0 29
// Total:	0 30

#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define Y first
#define X second
#define all(x) x.begin(), x.end()
#define SortVec(x) sort(all(x))
#define CompressVec(x) x.erase(unique(all(x)), x.end())
#define ExistInVec(x, value) find(all(x), value) != x.end()

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

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<bool> visited(n + 1);
    vector<vector<int>> adj(n + 1);

    for (int i = 0; i < n - 1; ++i)
    {
        int a, b;
        cin >> a >> b;
        adj[a].pb(b);
        adj[b].pb(a);
    }

    queue<int> path;
    for (int i = 0; i < n; ++i)
    {
        int num;
        cin >> num;
        path.push(num);
    }

    int firstNum = path.front();
    path.pop();
    if (firstNum != 1)
    {
        cout << 0;
        return 0;
    }

    queue<int> q;
    visited[firstNum] = true;
    q.push(firstNum);

    while (!q.empty())
    {
        int node = q.front();
        q.pop();

        int count = 0;
        for (auto nNode : adj[node])
        {
            if (visited[nNode]) continue;
            visited[nNode] = true;
            ++count;
        }

        for (int i = 0; i < count; ++i)
        {
            int nNode = path.front();
            path.pop();

            if (!visited[nNode])
            {
                cout << 0;
                return 0;
            }

            q.push(nNode);
        }
    }

    cout << 1;
    return 0;
}
