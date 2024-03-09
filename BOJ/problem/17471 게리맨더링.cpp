// URL: https://www.acmicpc.net/problem/17471
// Algo: 브루트 포스, 조합, BFS

// Start:	240309 22 45
// Read:	0 1
// Think:	0 21
// Code:	0 30
// Total:	0 52

// 이렇게 n이 10처럼 작은 수면 브루트 포스 생각해보기. MST나 1<<n 사이즈의 dp처럼 이상하게 생각하다가 겨우 떠오름.
// 선거구가 3개일 경우 처리하는 법 잘못 생각해서 헤멤. 단순히 노드끼리 최소 하나 이상 서로 연결되어 있는 식으로는 안 되고 (반례 1-2-X-3-4)
// BFS 돌려서 한 노드에서 모든 노드까지 방문 가능한지를 확인해야함.

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

int         n;
int         people[11];
vector<int> adj[11];
bool        visited[11];

bool CheckConnected(const vector<int>& select)
{
    memset(visited, true, sizeof(visited));
    for (auto node : select)
        visited[node] = false;

    queue<int> q;
    visited[select[0]] = true;
    q.push(select[0]);
    int connected = 1;

    while (!q.empty())
    {
        int node = q.front();
        q.pop();

        for (auto dest : adj[node])
        {
            if (visited[dest]) continue;
            visited[dest] = true;
            q.push(dest);
            ++connected;
        }
    }

    return connected == select.size();
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int totalSum = 0;

    cin >> n;
    for (int i = 1; i <= n; ++i)
    {
        cin >> people[i];
        totalSum += people[i];
    }

    for (int i = 1; i <= n; ++i)
    {
        int num;
        cin >> num;
        for (int j = 0; j < num; ++j)
        {
            int dest;
            cin >> dest;
            adj[i].pb(dest);
        }
    }

    int answer = INF;
    for (int selectNum = n / 2; selectNum > 0; --selectNum)
    {
        vector<bool> comb(n, true);
        for (int i = 0; i < selectNum; ++i)
        {
            comb[i] = false;
        }

        do
        {
            vector<int> select;
            vector<int> nonSelect;

            int selectSum = 0;
            for (int i = 0; i < n; ++i)
            {
                if (!comb[i])
                {
                    select.pb(i + 1);
                    selectSum += people[i + 1];
                }
                else
                {
                    nonSelect.pb(i + 1);
                }
            }

            if (!CheckConnected(select)) continue;
            if (!CheckConnected(nonSelect)) continue;

            answer = min(answer, abs(totalSum - 2 * selectSum));
        }
        while (next_permutation(all(comb)));
    }

    if (answer == INF) cout << -1;
    else cout << answer;
}
