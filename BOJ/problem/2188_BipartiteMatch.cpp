// 이런건 이분매칭하자 후

#include <bits/stdc++.h>
using namespace std;
const int MAX_V = 201;
vector<int> adj[MAX_V];
bool visit[MAX_V];
int room[MAX_V];

int dfs(int cow)
{
    if (visit[cow])
        return 0;
    visit[cow] = true;
    for (int w : adj[cow])
    {
        if (room[w] == -1 || dfs(room[w]))
        {
            room[w] = cow;
            return 1;
        }
    }
    return 0;
}

int main()
{
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; ++i)
    {
        int si;
        cin >> si;
        while (si--)
        {
            int val;
            cin >> val;
            adj[i].push_back(val);
        }
    }

    int ans = 0;
    fill(room, room + MAX_V, -1);
    for (int i = 1; i <= n; ++i)
    {
        fill(visit, visit + MAX_V, false);
        if (dfs(i))
        {
            ++ans;
        }
    }
    cout << ans;
}
