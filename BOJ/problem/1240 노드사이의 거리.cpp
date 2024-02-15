// URL: https://www.acmicpc.net/problem/1240
// Algo: BFS, DFS 인접 리스트 기본

// 2년만에 코테 복귀. 다 까먹었다..

// Start:	240205 14 35
// Read:	0 0
// Think:	0 20
// Code:	0 37
// Total:	0 57

#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define all(x) x.begin(), x.end()
#define sortvec(x) sort(all(x))
#define compress(x) x.erase(unique(all(x)), x.end())
#define findvec(x, value) find(all(x), value) != x.end()

using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;

const ll  MOD = 1000000007;
const int INF = 0x3f3f3f3f;
const ll  LLINF = 1e18;


vector<pii> tree[1001];
bool visited[1001];

int BFS(int start, int end)
{
    queue<pii> q;

    visited[start] = true;
    q.push({start, 0});

    while (!q.empty())
    {
        auto [node, dist] = q.front();
        q.pop();

        // 종료
        if (node == end)
        {
            return dist;
        }

        for (auto [cNode, cDist] : tree[node])
        {
            if (visited[cNode]) continue;
            visited[cNode] = true;
            q.push({cNode, cDist + dist});
        }
    }

    return -1; // Fucked
}


int DFS(int start, int end)
{
    stack<pii> s;

    visited[start] = true;
    s.push({start, 0});

    while (!s.empty())
    {
        int node = s.top().F;
        int dist = s.top().S;
        s.pop();

        // 종료
        if (node == end)
        {
            return dist;
        }

        for (pii child : tree[node])
        {
            int cNode = child.F;
            int cDist = child.S;

            if (visited[cNode]) continue;
            visited[cNode] = true;
            s.push({cNode, cDist + dist});
        }
    }

    return -1; // Fucked
}

int DFSAnswer = 0;
void DFSRecur(int cur, int end, int dist)
{
    visited[cur] = true;

    if (cur == end)
    {
        DFSAnswer = dist;
        return;
    }

    for (pii child: tree[cur])
    {
        int cNode = child.F;
        int cDist = child.S;

        if (visited[cNode]) continue;
        DFSRecur(cNode, end, dist + cDist);
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    cin >> N >> M;

    for (int i = 0; i < N -1; ++i)
    {
        int n1, n2, dist;
        cin >> n1 >> n2 >> dist;


        tree[n1].pb({n2, dist});
        tree[n2].pb({n1,dist});
    }

    for (int i = 0; i < M; ++i)
    {
        memset(visited, false, sizeof(visited));

        int start, end;
        cin >> start >> end;

        // cout << BFS(start, end) << '\n';
        // cout << DFS(start, end) << '\n';

        DFSAnswer = 0;
        DFSRecur(start, end, 0);
        cout << DFSAnswer << '\n';
    }
}
