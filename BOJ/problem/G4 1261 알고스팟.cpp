// URL: https://www.acmicpc.net/problem/1261
// Algo: 0-1 BFS or 다익스트라

// Start:	240519 21 45
// Read:	0 2
// Think:	0 2
// Code:	0 10
// Total:   0 14

// 0-1 BFS 알고리즘: '가중치가 0 혹은 1인 그래프'에서 최단거리를 효율적으로 구하는 알고리즘

// '가중치 그래프에서 최단거리 구하기' 문제인만큼 다익스트라로 풀리긴 하나
// 다익스트라는 O(ElogE)임에 비해, 0-1 BFS는 BFS O(V+E)로 훨씬 더 효율적이다.

// 다익스트라처럼 최단거리 배열 D와 인접간선 배열 adj를 동일하게 사용하며
// 최단거리가 줄어드는 경우에만 삽입한다는 점에서 코드가 유사하지만

// 우선순위 큐 대신 덱을 쓰며, 삽입을 앞 혹은 뒤에 한다.
// (마찬가지로 D가 visited의 역할을 하기 때문에 visited 배열은 필요 없다)

// 원리: BFS에서 큐는 정점들의 레벨(거리, 가중치)순으로 항상 정렬되어 있어야하며,
// 큐 속에는 맨앞 정점의 레벨과 같거나 +1인 정점들만 존재한다.
// ex) (거리1, 거리1, 거리1, 거리2, 거리2)

// 따라서 최단거리가 줄어드는 탐색일 때,
// 가중치가 0인 인접 정점을 삽입할 때는 덱의 앞에 넣고,
// 가중치가 1인 인접 정점을 삽입할 때는 덱의 뒤에 넣으면
// 덱의 정렬이 유지되며 BFS를 정상적으로 돌릴 수 있다

// https://justicehui.github.io/medium-algorithm/2018/08/30/01BFS/
// https://soonyoung.medium.com/algorithm-bfs-0-1-bfs-b81693cfd858


#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);

constexpr int INF = 0x3f3f3f3f;
using pii = pair<int, int>;
using tiii = tuple<int, int, int>; 

int n, m;
int D[100][100];
int cost[100][100];

int dy[4] = {0, 1, 0, -1};
int dx[4] = {1, 0, -1, 0}; // 동남서북
bool OOB(int y, int x) { return y < 0 || y >= n || x < 0 || x >= m; }

int main()
{
    fastio;
    memset(D, 0x3f, sizeof(D));
    cin >> m >> n;

    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < m; ++j)
        {
            char c;
            cin >> c;
            cost[i][j] = c - '0';
        }
    }

    // 0-1 BFS 풀이
    // y, x
    deque<pii> dq;
    D[0][0] = 0;
    dq.push_front({0, 0});

    while (!dq.empty())
    {
        auto [y, x] = dq.front(); dq.pop_front();
        for (int i = 0; i < 4; ++i)
        {
            int ny = y + dy[i];
            int nx = x + dx[i];
            if (OOB(ny, nx)) continue;

            if (D[ny][nx] <= D[y][x] + cost[ny][nx]) continue;
            D[ny][nx] = D[y][x] + cost[ny][nx];

            if (cost[ny][nx]) dq.push_back({ny, nx});
            else dq.push_front({ny, nx});
        }
    }

    // 다익스트라 풀이
    /*
    // dist, y, x
    priority_queue<tiii, vector<tiii>, greater<>> pq;
    D[0][0] = 0;
    pq.push({D[0][0], 0, 0});

    while (!pq.empty())
    {
        auto [dist, y, x] = pq.top(); pq.pop();
        if (dist != D[y][x]) continue;

        for (int i = 0; i < 4; ++i)
        {
            int ny = y + dy[i];
            int nx = x + dx[i];
            if (OOB(ny, nx)) continue;

            if (D[ny][nx] <= dist + cost[ny][nx]) continue;
            D[ny][nx] = dist + cost[ny][nx];
            pq.push({D[ny][nx], ny, nx});
        }
    }
    */

    cout << D[n - 1][m - 1];
}


