// URL: https://www.acmicpc.net/problem/16437
// Algo: DFS, 트리

// Start:	240926 17 41
// Read:	0 2
// Think:	0 1
// Code:	0 8
// Total:	0 11

// 늑대가 양이 올 때마다 한 마리씩 먹는다는 건지, 평생 한 마리만 먹는다는 건지(이거였다)
// 헷갈려서 좋지 않은 문제인 듯

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) x.begin(), x.end()
#define pb push_back

using ll = long long;

int n;
vector<int> adj[123'457];
ll arr[123'457];

ll DFS(int cur, int parent)
{
    ll ret = arr[cur];
    for (const int nxt : adj[cur])
    {
        if (nxt == parent) continue;
        ret += DFS(nxt, cur);
    }

    if (ret < 0) ret = 0;
    return ret;
}

int main()
{
    fastio;
    cin >> n;
    for (int i = 2; i <= n; ++i)
    {
        char c;
        int p;
        cin >> c >> arr[i] >> p;

        if (c == 'W') arr[i] = -arr[i];
        adj[i].pb(p);
        adj[p].pb(i);
    }

    cout << DFS(1, -1);
}
