// URL: https://www.acmicpc.net/problem/17182
// Algo: 플로이드, 백트래킹 or 비트마스킹

// Start:	240720 14 05
// Read:	0 2
// Think:	0 7
// Code:	0 6
// Total:   0 15

// 외판원 순회 문제와 비슷하게 DFS에 depth 대신
// 방문여부를 표시하는 비트마스킹 dp를 넣으면 좀 더 빨라질 수 있다.

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) x.begin(), x.end()
#define pb push_back

constexpr int INF = 0x3f3f3f3f;

int n, start;
int dist[10][10];
bool visited[10];

int DFS(int cur, int depth, int sum)
{
    if (depth == n)
        return sum;

    int ret = INF;
    for (int i = 0; i < n; ++i)
    {
        if (visited[i]) continue;
        visited[i] = true;
        ret = min(ret, DFS(i, depth + 1, sum + dist[cur][i]));
        visited[i] = false;
    }
    return ret;
}

int main()
{
    fastio;
    cin >> n >> start;
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            cin >> dist[i][j];

    for (int k = 0; k < n; ++k)
        for (int s = 0; s < n; ++s)
            for (int e = 0; e < n; ++e)
                dist[s][e] = min(dist[s][e], dist[s][k] + dist[k][e]);

    visited[start] = true;
    cout << DFS(start, 1, 0);
}
