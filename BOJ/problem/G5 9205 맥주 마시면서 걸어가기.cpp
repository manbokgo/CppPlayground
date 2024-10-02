// URL: https://www.acmicpc.net/problem/9205
// Algo: BFS

// Start:	241002 15 06
// Read:	0 2
// Think:	0 1
// Code:	0 7
// Total:	0 10

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) x.begin(), x.end()
#define pb push_back

using pii = pair<int, int>;

pii pos[102];
bool visited[102];

int main()
{
    fastio;

    int T;
    cin >> T;

    while (T--)
    {
        memset(visited, false, sizeof(visited));

        int n;
        cin >> n;
        n += 2;

        for (int i = 0; i < n; ++i)
        {
            auto& [y, x] = pos[i];
            cin >> y >> x;
        }

        queue<int> q;
        visited[0] = true;
        q.push(0);

        bool success = false;
        while (!q.empty())
        {
            const int idx = q.front();
            q.pop();

            if (idx == n - 1)
            {
                success = true;
                break;
            }

            const auto [cy, cx] = pos[idx];
            for (int i = 0; i < n; ++i)
            {
                if (visited[i]) continue;

                const auto [ny, nx] = pos[i];
                if (abs(ny - cy) + abs(nx - cx) > 1000) continue;

                visited[i] = true;
                q.push(i);
            }
        }

        if (success) cout << "happy\n";
        else cout << "sad\n";
    }
}
