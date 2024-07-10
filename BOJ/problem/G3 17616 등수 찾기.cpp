// URL: https://www.acmicpc.net/problem/17616
// Algo: DFS or BFS

// Start:	240710 09 46
// Read:	0 1
// Think:	0 5
// Code:	0 10
// Total:	0 16

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) x.begin(), x.end()
#define pb push_back

vector<int> adj[100'001];
vector<int> rAdj[100'001];
bool visited[100'001];

int dCnt = 0;
int uCnt = 0;

void dDFS(int num)
{
    visited[num] = true;
    ++dCnt;
    for (const int nxt : adj[num])
    {
        if (!visited[nxt]) dDFS(nxt);
    }
}

void uDFS(int num)
{
    visited[num] = true;
    ++uCnt;
    for (const int nxt : rAdj[num])
    {
        if (!visited[nxt]) uDFS(nxt);
    }
}

int main()
{
    fastio;

    int n, m, x;
    cin >> n >> m >> x;

    while (m--)
    {
        int a, b;
        cin >> a >> b;
        adj[a].pb(b);
        rAdj[b].pb(a);
    }

    dDFS(x);
    uDFS(x);
    --uCnt;
    --dCnt;
    cout << 1 + uCnt << ' ' << n - dCnt;
}
