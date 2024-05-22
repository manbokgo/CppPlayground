// URL: https://www.acmicpc.net/problem/9466
// Algo: DFS, SCC 타잔

// Start:	240522 21 48
// Read:	0 3
// Think:	0 28
// Code:	0 21
// Total:	0 52
// 오모시로이

// DFS 함수 만들고 재귀 돌리려다가, 어차피 노드 간선이 하나 뿐이라서 그냥 while 루프가 더 깔끔하다는 거 깨닫고 바꿈

// 방문 배열과, 찐 방문 배열 2가지를 사용해야 한다.
// 방문은 되었지만 찐방문이 되어있지 않다면, 이번 루프에서 동일한 노드를 방문한 것이라고 판단 가능.

// 처음엔 찐방문 배열을 두는게 떠오르지 않아서, 마치 유니온 파인드처럼 탐색하는 노드들의 부모 노드(진입 노드)를
// 기준으로 잡는 식으로 생각했는데, 이러면 노드별로 별도의 인덱스를 세우고, 사이클이 형성된 곳까지 되찾아가는 과정...을
// 보고 너무 복잡하다고 판단해서 포기하고, 찐방문 배열 두고 루프를 여러번 도는 식으로 바꿔서 풀었다.

// 근데 다 풀고 나서 찾아보니 이런 문제의 유형이 강한 연결 요소(SCC, Strongly Connected Component) 문제인데
// 놀랍게도 대표적인 SCC 알고리즘인 '타잔의 알고리즘'이 내가 고민하던 것을 그대로 구현한 것으로,
// 이 문제에서 더 심화되어 노드의 '간선이 여러 개인 양방향 그래프'에도 적용할 수 있는 방식이었다. 헉...

// 당연히 타잔 알고리즘으로 구현해도 풀린다. 공부한 김에 P5 2150 Strongly Connected Component 문제도 날먹했다.

// https://storyofvector7.tistory.com/44
// https://velog.io/@namsh1125/%ED%83%80%EC%9E%94-%EC%95%8C%EA%B3%A0%EB%A6%AC%EC%A6%98

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) x.begin(), x.end()
#define pb push_back

// SCC 타잔 알고리즘
vector<int> adj[100'001];
int group[100'001];
bool finish[100'001];
stack<int> S;

int answer;
int nIdx = 1;

int Tarjan(int i)
{
    S.push(i);
    group[i] = nIdx++;

    int parent = group[i];
    for (const auto j : adj[i])
    {
        if (!group[j]) parent = min(parent, Tarjan(j));
        else if (!finish[j]) parent = min(parent, group[j]);
    }

    if (parent == group[i]) // 내가 부모 노드다
    {
        int cnt = 0;
        while (true)
        {
            int num = S.top();
            S.pop();

            ++cnt;
            finish[num] = true;
            if (num == i) break;
        }

        if (cnt > 1) answer -= cnt;
        else if (adj[i][0] == i) answer -= 1;
    }

    return parent;
}

int main()
{
    fastio;

    int T;
    cin >> T;
    while (T--)
    {
        for (auto& ad : adj) ad.clear();
        memset(group, 0, sizeof(group));
        memset(finish, false, sizeof(finish));
        while (!S.empty()) S.pop();
        nIdx = 0;

        int n;
        cin >> n;

        answer = n;
        for (int i = 1; i <= n; ++i)
        {
            int num;
            cin >> num;
            adj[i].pb(num);
        }

        for (int i = 1; i <= n; ++i)
        {
            if (!group[i]) Tarjan(i);
        }

        cout << answer << '\n';
    }
}


// DFS 제출 풀이
/*
int adj[100'001];
bool visited[100'001];
bool finish[100'001];

int main()
{
    fastio;

    int T;
    cin >> T;
    while (T--)
    {
        memset(visited, false, sizeof(visited));
        memset(finish, false, sizeof(finish));

        int n;
        cin >> n;
        for (int i = 1; i <= n; ++i)
        {
            cin >> adj[i];
        }

        int answer = n;
        for (int i = 1; i <= n; ++i)
        {
            if (!visited[i])
            {
                int cur = i;
                while (true)
                {
                    visited[cur] = true;
                    const int nxt = adj[cur];
                    if (finish[nxt]) // 이미 확정된 노드에 도달
                    {
                        cur = i;
                        while (!finish[cur])
                        {
                            finish[cur] = true;
                            cur = adj[cur];
                        }
                        break;
                    }

                    if (visited[nxt] && !finish[nxt]) // 똑같은 노드를 또 방문
                    {
                        while (!finish[cur]) // 사이클 이룬 노드들 확정
                        {
                            --answer;
                            finish[cur] = true;
                            cur = adj[cur];
                        }

                        cur = i;
                        while (!finish[cur]) // i~사이클까지의 노드들 확정
                        {
                            finish[cur] = true;
                            cur = adj[cur];
                        }
                        break;
                    }

                    cur = nxt;
                }
            }
        }

        cout << answer << '\n';
    }
}
*/
