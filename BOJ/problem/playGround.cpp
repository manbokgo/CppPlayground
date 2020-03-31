#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>
#include <memory.h>
#include <string.h>
#include <stack>

#define MAX 5001
#define INF 987654321

using namespace std;

// 모든 배열은 용량이 1이기에 bool로 선언 가능
// 그리고, 한번만 방문하기에 c, f배열이 2가 될 수 없음
// 무조건 0 또는 1
bool c[MAX][MAX];  // capacity :: i->j로 가는 간선 용량
bool f[MAX][MAX];  // flow :: i->j로 현재 흐르고 있는 유량
bool visit[MAX];   // 방문 배열
bool tmp[MAX];     // 방문 배열 복사
bool already[MAX]; // 메모이제이션을 위한 배열
bool chk[MAX];     // 메모이제이션을 위한 배열

int main()
{
    int n, p, tCase = 1;

    while (1)
    {
        memset(c, 0, sizeof(c));
        memset(f, 0, sizeof(f));
        memset(visit, false, sizeof(visit));
        memset(tmp, false, sizeof(tmp));
        memset(already, false, sizeof(already));
        stack<int> st;

        vector<int> adj[MAX];

        // 입력
        scanf("%d %d", &n, &p);
        if (n == 0 && p == 0)
            break;

        for (int i = 1; i <= p; i++)
        {
            // adj 벡터에 중복 입력을 막기위해 이용
            memset(chk, false, sizeof(chk));

            while (1)
            {
                int to;
                char ch;
                scanf("%d%c", &to, &ch);

                // i에 의해 to에도 이미 값이 들어간다면 중복이기에
                // 나중에 to가 i가될 때 to에서 i로 값이 들어오는것을 방지
                if (!already[i])
                    already[i] = true;

                if (!already[to])
                {
                    // to에 이미 값이 한번 들어왔다면
                    // 그 값으로 인해 i와 to는 또 중복이 생기는 것을 방지
                    if (!chk[to])
                    {
                        chk[to] = true;
                        c[i][to] = 1;
                        c[to][i] = 1;

                        adj[i].push_back(to);
                        adj[to].push_back(i);
                    }
                }
                if (ch == '\n')
                    break;
            }
        }

        int totalFlow = 0, S = 1, T = 2; // S :: source, T :: sink

        // 증가 경로를 못 찾을 때까지
        while (1)
        {
            int prev[MAX];
            memset(prev, -1, sizeof(prev));

            queue<int> q;
            // 싱크를 처음 push 해준다.
            q.push(S);

            while (!q.empty())
            {
                int cur = q.front();
                q.pop();

                if (cur != S && cur != T)
                    visit[cur] = true;

                for (int i = 0; i < adj[cur].size(); i++)
                {
                    int next = adj[cur][i];

                    // next를 방문하였다면 continue
                    if (prev[next] != -1 || next == S)
                        continue;

                    // 아직 흐를 수 있는 유량이 있다면
                    // 즉, cur -> next로 갈 수 있는 유량이 있다면
                    if (!visit[next] && c[cur][next] - f[cur][next] > 0)
                    {
                        q.push(next);

                        // next의 경로 추적을 위해 저장
                        prev[next] = cur;

                        // 만약 next가 sink면 break
                        if (next == T)
                            break;
                    }
                }
            }

            memset(visit, false, sizeof(visit));

            // source -> sink의 간선이 없다면 break;
            if (prev[T] == -1)
                break;

            // 해당 경로에 flow를 보낸다.
            // 그리고 역방향으로는 flow를 빼준다.

            // memcpy를 통해 방문 위치를 계속해서 기록해둔다.(중복 방문 방지)
            memcpy(visit, tmp, sizeof(tmp));

            for (int i = T; i != S; i = prev[i])
            {
                st.push(i);
                f[prev[i]][i] = 1;
                f[i][prev[i]] = 0;

                if (i != S && i != T)
                    visit[i] = true;
            }

            memcpy(tmp, visit, sizeof(visit));

            st.push(1);

            totalFlow++;
        }

        printf("Case %d:\n", tCase++);
        // n개만 출력(n개 이상의 경로가 있어도)
        if (totalFlow >= n)
        {
            while (!st.empty() && n)
            {
                printf("%d ", st.top());
                if (st.top() == 2)
                {
                    n--;
                    printf("\n");
                }
                st.pop();
            }
        }

        else
            printf("Impossible\n");

        printf("\n");
    }

    return 0;
}