// URL: https://www.acmicpc.net/problem/1260
// Algo: BFS, DFS 기본 (인접 리스트)

// Start:	240218 01 25
// Read:	0 0
// Think:	0 0
// Code:	0 10
// Total:	0 10

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

vector<int> graph[1005];
bool        visited[1005];

vector<int> routes;

void BFS(int start)
{
    queue<int> q;

    visited[start] = true;
    q.push(start);

    while (!q.empty())
    {
        int node = q.front();
        q.pop();

        routes.pb(node);

        for (int cNode : graph[node])
        {
            if (visited[cNode]) continue;
            visited[cNode] = true;
            q.push(cNode);
        }
    }
}

void DFS(int node)
{
    visited[node] = true;
    routes.pb(node);

    for (int cNode : graph[node])
    {
        if (visited[cNode]) continue;
        DFS(cNode);
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M, V;
    cin >> N >> M >> V;

    while (M--)
    {
        int st, en;
        cin >> st >> en;

        graph[st].pb(en);
        graph[en].pb(st);
    }

    for (int i = 1; i <= N; ++i)
    {
        sort(all(graph[i]));
    }

    DFS(V);

    for (int route : routes)
    {
        cout << route << " ";
    }
    cout << "\n";

    // 초기화
    routes.clear();
    memset(visited, false, sizeof(visited));

    BFS(V);
    for (int route : routes)
    {
        cout << route << " ";
    }
    cout << "\n";
}
