// URL: https://www.acmicpc.net/problem/16928
// Algo: BFS

// Start:	250123 08 36
// Read:	0 2
// Think:	0 2
// Code:	0 5
// Total:	0 9

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) x.begin(), x.end()
#define pb push_back

int jump[101];
bool visited[101];

int main()
{
    fastio;

    int n, m;
    cin >> n >> m;

    while (n--)
    {
        int x, y;
        cin >> x >> y;
        jump[x] = y;
    }

    while (m--)
    {
        int u, v;
        cin >> u >> v;
        jump[u] = v;
    }

    queue<int> q;
    visited[1] = true;
    q.push(1);

    int cnt = 1;
    while (!q.empty())
    {
        int qsz = q.size();
        while (qsz--)
        {
            const int cur = q.front();
            q.pop();
            for (int i = 1; i <= 6; ++i)
            {
                int nxt = cur + i;
                if (nxt > 100) continue;
                if (jump[nxt]) nxt = jump[nxt];
                if (nxt == 100)
                {
                    cout << cnt;
                    return 0;
                }

                if (visited[nxt]) continue;
                visited[nxt] = true;
                q.push(nxt);
            }
        }
        ++cnt;
    }
}
