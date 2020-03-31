#include <bits/stdc++.h>
using namespace std;
const int MAX_V = 1001;
vector<int> adj[MAX_V];
bool visit[MAX_V];
int book[MAX_V];

int dfs(int stud)
{
    visit[stud] = true;
    for (int w : adj[stud])
    {
        if (book[w] == -1 || !visit[book[w]] && dfs(book[w]))
        {
            book[w] = stud;
            return 1;
        }
    }
    return 0;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--)
    {
        int n, m;
        cin >> n >> m;
        for (int i = 0; i < m; ++i)
        {
            int a, b;
            cin >> a >> b;
            adj[i].clear();
            for (int j = a; j <= b; j++)
            {
                adj[i].push_back(j);
            }
        }

        int ans = 0;
        fill(book, book + MAX_V, -1);
        for (int i = 0; i < m; ++i)
        {
            fill(visit, visit + MAX_V, false);
            if (dfs(i))
            {
                ++ans;
            }
        }
        cout << ans << "\n";
    }
}
