// URL: https://www.acmicpc.net/problem/5214
// Algo: BFS (+변형)

// Start:	240306 19 02
// Read:	0 0
// Think:	0 3
// Code:	0 10  메모리 초과
// Code:	0 15  n=1일 때 생각못해서 10분 날려먹음
// Total:	0 28
// 오모시로이

// 현명하지 못한 자가 늘 그렇듯 의도한대로 메모리 초과로 한번 터짐
// 한 하이퍼튜브가 서로 연결하는 역의 개수가 k개 일때 인접리스트로 간선을 만들면, 간선 개수는 k개 중 2개를 구하는 조합으로
// 대충 한 튜브당 k^2개임. k가 1000이고, 튜브 개수 m이 1000개면  1000^2 x 1000 = 1000^3개의 간선 = 10억 개의 int = 4000 mb 터진다!
// 당연히 인접 행렬하면 [10만][10만]  100억 개의 int로 터지고. 애초에 간선 개수가 1000^3인 시점에서 BFS O(V+E)는 통과 못할듯

// 해결법은 튜브 자체가 일종의 더미 노드가 되어, 튜브에 속해있는 노드들에게 간선을 놓는 것.
// 예를 들어, 노드 4개가 서로에게 모두 연결되어있을 떄 간선 수는 6개지만, 가운데에 더미 노드를 두면 간선 수는 4개인 원리.
// 이러면 튜브당 간선 수는 k개고, 이런 튜브가 m개이니 총 간선 수는 1000^2로 메모리도 되고 시간 복잡도도 된다.
// BFS O(V+E)에서 V가 n+m이고, E는 km. 노드+튜브(더미노드)를 몽땅 큐에 넣고 BFS 돌리는게 명쾌한 듯.

// 내 (첫) 풀이는 튜브를 싹 배열에 저장해놓고, 특정 노드가 어느 튜브들에 속해있는지만 저장해놓는 식으로
// 노드->튜브 간선과 튜브->노드 간선을 분리해서 보고 접근했음

// 그냥 큐에 노드를 넣고(visited[node]) 푸니깐 1072ms 나왔는데, 큐에 튜브를 넣는 걸로(visited[tube]) 바꿔서 푸니 196ms로 줄어듦
// 풀이의 BFS가 튜브 1개 거쳤을 때, 2개 거쳤을 때... 하면서 단계별로 뛰는 것이니 의미적으로도 visited[tube]로 접근하는게 맞음
// 이 방식 자체가 시간복잡도 상 일반 BFS와 좀 다르다.

// 큐에 노드 넣으면 큐에 n개 들어가고, 노드마다 연결된 ?개 튜브(총합 E)를 접근하고, 각 튜브에 속한 노드 k개를 접근하니 연산 횟수는 n+Ek
// 큐에 튜브 넣으면 큐에 m개 들어가고, 튜브마다 연결된 k개 노드를 접근하고, 각 노드가 속한 튜브 ?개(총합 E)를 접근하니 연산 횟수는 km+E
// 전자는 결국 1000^3이고, 후자는 1000^2이다. 위에서 말한 명쾌한 방법이랑 시간 비슷하게 나옴.
// 그냥 정석대로 명쾌한 방법 쓰는게 맞을 듯


#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define Y first
#define X second
#define all(x) x.begin(), x.end()
#define sortVec(x) sort(all(x))
#define compress(x) x.erase(unique(all(x)), x.end())
#define existInVec(x, value) find(all(x), value) != x.end()

using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using tiii = tuple<int, int, int>;
using tlll = tuple<ll, ll, ll>;

constexpr int INF = 0x3f3f3f3f;


// 명쾌한 풀이
int n, k, m;

vector<int> nodes[101'001]; // 노드 + (100'001, 101'000] 튜브(더미노드)
int depth[101'001]; // visited 겸 depth

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> k >> m;
    if (n == 1)
    {
        cout << 1;
        return 0;
    }

    for (int i = 1; i <= m; ++i)
    {
        for (int j = 0; j < k; ++j)
        {
            int num;
            cin >> num;
            nodes[num].pb(100'000 + i);
            nodes[100'000 + i].pb(num);
        }
    }

    queue<int> q;
    depth[1] = 1;
    q.push(1);

    while (!q.empty())
    {
        auto node = q.front();
        q.pop();

        // if (nNode == n) 조건을 이 곳에 넣으면 n == 1 케이스를 선처리하지 않아도 됨
        // 쓸데없이 더 연산을 한다는 게 단점이긴 한데 실수 줄이려면 그냥 여기다가 넣는 게 맞을지도?

        for (auto nNode : nodes[node])
        {
            if (nNode == n)
            {
                cout << depth[node];
                return 0;
            }

            if (depth[nNode]) continue;

            if (nNode > 100'000) depth[nNode] = depth[node] + 1;
            else depth[nNode] = depth[node];
            q.push(nNode);
        }
    }

    cout << -1;
}



/*
// 196ms 풀이. 튜브를 큐에 visited[tube]
// for (auto nNode : tubes[tube])
//   for (auto tube : belong[node])

int n, k, m;

vector<int> tubes[1'001]; // 튜브에서 노드까지의 간선
vector<int> belong[100'001]; // 노드에서 튜브까지의 간선
bool        visited[1'001]; // 튜브 방문

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> k >> m;

    if (n == 1) // 실수: n이 1이면 바로 리턴
    {
        cout << 1;
        return 0;
    }

    for (int i = 0; i < m; ++i)
    {
        for (int j = 0; j < k; ++j)
        {
            int num;
            cin >> num;
            tubes[i].pb(num);
            belong[num].pb(i);
        }
    }

    queue<pii> q; // 튜브, 단계
    for (auto tube : belong[1])
    {
        visited[tube] = true;
        q.push({tube, 1});
    }

    while (!q.empty())
    {
        auto [tube, depth] = q.front();
        q.pop();

        for (auto nNode : tubes[tube])
        {
            if (nNode == n)
            {
                cout << depth + 1;
                return 0;
            }

            for (auto nTube : belong[nNode])
            {
                if (visited[nTube]) continue;
                visited[nTube] = true;
                q.push({nTube, depth + 1});
            }
        }
    }

    cout << -1;
}
*/


// 1072ms 풀이. 일반적인 경우처럼 노드를 큐에 visited[node]
// for (auto tube : belong[node])
//   for (auto nNode : tubes[tube])

/*
 int n, k, m;

vector<int> tubes[1001];
vector<int> belong[100'001];
bool        visited[100'001];

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> k >> m;

    if (n == 1) // 실수:
    {
        cout << 1;
        return 0;
    }

    for (int i = 0; i < m; ++i)
    {
        for (int j = 0; j < k; ++j)
        {
            int num;
            cin >> num;
            tubes[i].pb(num);
            belong[num].pb(i);
        }
    }

    queue<pii> q; // 정점, 단계
    visited[1] = true;
    q.push({1, 1});

    while (!q.empty())
    {
        auto [node, depth] = q.front();
        q.pop();

        for (auto tube : belong[node])
        {
            for (auto nNode : tubes[tube])
            {
                if (nNode == n)
                {
                    cout << depth + 1;
                    return 0;
                }

                if (visited[nNode]) continue;;
                visited[nNode] = true;
                q.push({nNode, depth + 1});
            }
        }
    }

    cout << -1;
}
*/