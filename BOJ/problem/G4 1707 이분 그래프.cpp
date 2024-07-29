// URL: https://www.acmicpc.net/problem/1707
// Algo: 이분 그래프(BFS)

// Start:	240729 16 06
// Read:	0 2
// Think:	0 7
// Code:	0 10
// Total:	0 19

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) x.begin(), x.end()
#define pb push_back

vector<int> adj[20'001];
int visited[20'001];

bool BFS(int st)
{
    queue<int> q;
    visited[st] = 1;
    q.push(st);

    while (!q.empty())
    {
        const int cur = q.front();
        q.pop();

        for (const int nxt : adj[cur])
        {
            if (visited[nxt] == 0)
            {
                visited[nxt] = visited[cur] * -1;
                q.push(nxt);
                continue;
            }

            if (visited[nxt] == visited[cur])
            {
                return false;
            }
        }
    }

    return true;
}

int main()
{
    fastio;
    int T;
    cin >> T;

    while (T--)
    {
        for (auto& ad : adj) ad.clear();
        memset(visited, 0, sizeof(visited));

        int n, m;
        cin >> n >> m;
        while (m--)
        {
            int a, b;
            cin >> a >> b;
            adj[a].pb(b);
            adj[b].pb(a);
        }

        bool good = true;
        for (int i = 1; i <= n; ++i)
        {
            if (visited[i] == 0)
            {
                if (!BFS(i))
                {
                    good = false;
                    break;
                }
            }
        }

        cout << (good ? "YES\n" : "NO\n");
    }
}
