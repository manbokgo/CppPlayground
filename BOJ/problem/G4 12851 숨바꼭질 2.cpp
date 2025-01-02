// URL: https://www.acmicpc.net/problem/12851
// Algo: BFS

// Start:	250102 16 09
// Read:	0 1
// Think:	0 5
// Code:	0 34
// Total:	0 40

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) x.begin(), x.end()
#define pb push_back

constexpr int INF = 0x3f3f3f3f;

int visited[100'001];

int main()
{
    fastio;

    memset(visited, INF, sizeof(visited));

    int n, k;
    cin >> n >> k;

    if (n == k)
    {
        cout << 0 << '\n' << 1;
        return 0;
    }

    queue<int> q;

    visited[n] = 0;
    q.push(n);

    int answer = 0;
    while (!q.empty())
    {
        const int cur = q.front();
        q.pop();

        const int t = visited[cur];

        if (cur == k) ++answer;
        if (visited[k] <= t) continue; // 최소 시간 이상이면 더 이상 탐색할 필요 없음

        for (const int nxt : {cur - 1, cur + 1, cur * 2})
        {
            if (nxt < 0 || nxt > 100'000) continue;
            if (visited[nxt] < t + 1) continue; // 모든 경로를 탐색해야 하므로 동일한 시간도 큐에 넣어야 함

            visited[nxt] = t + 1;
            q.push(nxt);
        }
    }

    cout << visited[k] << '\n' << answer;
}
