// URL: https://www.acmicpc.net/problem/16947
// Algo: BFS, DFS or 위상 정렬 or SCC 타잔

// Start:	240929 19 17
// Read:	0 1
// Think:	0 46
// Code:	0 18
// Total:	1 5
// 오모시로이

// 정점 n개에 간선이 n개라면, 이 그래프에서는 무조건 사이클이 하나 뿐이라는 것을 캐치하지 못해서 엄청 오래 걸림

// 그래프에서 사이클이 여러 개인데다, 정점당 간선도 여러 개에 양방향이네? 라고 문제를 파악해서
// 아무리 생각해도 단순 DFS로는 풀 수 없고, G3 9466에서 배웠던 타잔 알고리즘만으로만 풀 수 있다고 판단했다.
// 그러면 골3짜리 문제는 아닌데... 고민하다 결국 타잔으로 풀었다.

// 다 풀고나서 보니 사이클이 하나인만큼, 단순하게 DFS 돌다가 사이클 찾으면 다른 간선을 더 탐색하지 않고 탈출하는 것으로도 가능하고
// 사이클에서 가장 먼 노드부터 위상 정렬을 시작하여, indegree가 1인 것들을 삭제하다 남는 것들이 사이클이라고 판정할 수도 있다.

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) x.begin(), x.end()
#define pb push_back

vector<int> adj[3'001];

int label[3'001];
bool finish[3'001];
stack<int> S;
vector<int> scc;
int labelIdx = 1;

bool cycle[3'001];
int dist[3'001];

// 양방향인만큼 직전 노드를 다시 방문해 사이클로 판정될 수 있기 때문에
// 문제 조건 상, 직전 노드는 탐색에서 제외하도록 수정
int Tarjan(int i, int from)
{
    S.push(i);
    label[i] = labelIdx++;

    int parent = label[i];
    for (const auto j : adj[i])
    {
        if (j == from) continue;
        if (!label[j]) parent = min(parent, Tarjan(j, i));
        else if (!finish[j]) parent = min(parent, label[j]);
    }

    if (parent == label[i]) // 내가 부모 노드다
    {
        scc.clear();
        while (true)
        {
            int num = S.top();
            S.pop();

            scc.pb(num);
            finish[num] = true;
            if (num == i) break;
        }

        if (scc.size() > 1)
        {
            for (const int num : scc)
                cycle[num] = true;
        }
    }

    return parent;
}

int main()
{
    fastio;
    memset(dist, -1, sizeof(dist));

    int n;
    cin >> n;

    for (int i = 1; i <= n; ++i)
    {
        int a, b;
        cin >> a >> b;
        adj[a].pb(b);
        adj[b].pb(a);
    }

    for (int i = 1; i <= n; ++i)
    {
        if (!label[i]) Tarjan(i, -1);
    }

    // BFS
    queue<int> q;
    for (int i = 1; i <= n; ++i)
    {
        if (cycle[i])
        {
            dist[i] = 0;
            q.push(i);
        }
    }

    while (!q.empty())
    {
        const int cur = q.front();
        q.pop();

        for (const int nxt : adj[cur])
        {
            if (dist[nxt] != -1) continue;
            dist[nxt] = dist[cur] + 1;
            q.push(nxt);
        }
    }

    for (int i = 1; i <= n; ++i)
    {
        cout << dist[i] << ' ';
    }
}
