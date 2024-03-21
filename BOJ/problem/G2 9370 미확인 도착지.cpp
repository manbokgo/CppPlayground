// URL: https://www.acmicpc.net/problem/9370
// Algo: 다익스트라

// Start:	240314 19 55
// Read:	0 2
// Think:	0 1
// Code:	0 16    전역변수 테케마다 초기화하는거 좀 잘하셈
// Code:	1 06    바보짓으로 30분+30분 날림
// Total:	1 25
// 오모시로이

/*
E가 최대 5만인 테케를 최대 100번하니, 총 500만으로 대략 300만까지 안전선인 O(ElogE) 3초에도 아슬아슬하다고 봤음
첫 제출에 시간초과라길래 시간복잡도 문제인가하고 이것저것 시도하느라 30분 날림.

삽질 끝에 여러 경우를 생각해서 넣어보니 만약 후보 노드가 아무와도 연결 안 된 동떨어진 노드라면
애초에 시작 노드까지의 경로가 없으니, 시작 노드까지 도달하면 종료되는 루프가 끝나지 않아 무한 루프한 거 였다.

제출 전에도 최단 경로 여러 개가 가능하다는 건 알았는데, 틀렸습니다 뜨면 고쳐야지하고 안일하게 제출했다가
무한루프로 시간초과 뜬 것을 아! 애초에 이 접근이 시간복잡도가 안 되는거구나!하고 착각하고 삽질한거였다...
최단 경로 여러 개 저장하도록 만들었으면 아예 경로가 없는 경우도 같이 처리할 수 있었는데...

쎄한 거 있으면 간 보지 말고 그냥 적용할 것. 제발.

그래서 최단 경로 여러개를 저장할 수 있도록 pre를 vector 배열로 바뀌었는데 틀렸습니다 뜸.
왜 그런지 짱구만 굴리면서 30분 생각하면서 헤매다가, 직접 테스트케이스 하나 만들어서 디버깅해보니
108번줄 if (d[nNode] > d[node] + nCost) 상황에서 pre.clear()를 빼먹었다는 점을 이제야! 깨닫고 정답.
d[nNode] == d[node] + nCost일때만 pre에 pb해서 여러 최단 경로를 저장하는 거다...

앞으론 머릿 속에서 테스트케이스 시뮬 돌리지말고 직접 넣어서 확인해볼 것. 제발.

st와 G(H)을 각각 시작점으로 다익스트라를 2(3)회 돌려서 최소 비용을 비교해 푸는 법도 떠오르긴 했었지만
위에서 말한 시간 초과 위험에, 1번만 돌리고 경로 저장하면 되는데 굳이? 싶어서 안 했는데
다른 사람 코드 보니 시간 차이도 거의 없고 이 방법은 헤멜만한 부분도 거의 없었다. 후...

또다른 방법1: 간선 정보에 mid1-mid2 간선을 통과한 후 방문하는 간선인지 표시하는 bool을 넣음
그런 간선을 통해 어떤 노드를 최소 비용으로 방문한다면 (d[nNode] == d[node] + nCost)
노드에 통과 표시 bool을 true로 하고, true인 노드면 mid1-mid2 간선을 통과해서 최소 비용으로 도달할 수 있다고 판별 가능
이러면 경로 역추적이 필요없다. 괜찮음.

또다른 방법2: 입력 받을 때 모든 간선 비용을 *2로 하여 짝수로 만들고, 특별히 mid1-mid2 간선만 추가로 -1하여 홀수로 만듦
이후 다익스트라를 평범하게 돌려서 최소 비용이 홀수인 것으로 판별 가능
만약 최단 경로가 여러 개 있더라도, mid1-mid2 간선 비용을 -0.5한만큼
항상 mid1-mid2 간선을 지나는 최단 경로를 우선하게 됨. 훌륭하고 깔끔함.
*/

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

vector<pii> adj[2001]; // {비용, 도착노드}
array<int, 2001> d;
vector<int> pre[2001];
array<int, 101> candidate;


int n, m, t;
int st, mid1, mid2;

bool Check(int node)
{
    if (node == st) return false;
    for (int preNode : pre[node])
    {
        if ((node == mid1 && preNode == mid2) ||
            (node == mid2 && preNode == mid1))
        {
            return true;
        }

        bool bFind = Check(preNode);
        if (bFind) return true;
    }

    return false;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--)
    {
        for (auto& ad : adj) ad.clear();
        for (auto& ad : pre) ad.clear();
        fill(all(d), INF);

        cin >> n >> m >> t;
        cin >> st >> mid1 >> mid2;

        for (int i = 0; i < m; ++i)
        {
            int a, b, cost;
            cin >> a >> b >> cost;
            adj[a].pb({cost, b});
            adj[b].pb({cost, a});
        }

        for (int i = 0; i < t; ++i)
        {
            cin >> candidate[i];
        }
        sort(candidate.begin(), candidate.begin() + t);

        priority_queue<pii, vector<pii>, greater<>> pq;
        d[st] = 0;
        pq.push({d[st], st});

        while (!pq.empty())
        {
            auto [cost, node] = pq.top();
            pq.pop();
            if (d[node] != cost) continue;

            for (auto [nCost, nNode] : adj[node])
            {
                if (d[nNode] < d[node] + nCost) continue;
                if (d[nNode] > d[node] + nCost)
                {
                    pre[nNode].clear(); // 실수: 이 줄 깜빡해서 30분 날림
                    d[nNode] = d[node] + nCost;
                    pq.push({d[nNode], nNode});
                }
                pre[nNode].pb(node);
            }
        }

        vector<int> answer;
        for (int i = 0; i < t; ++i)
        {
            if (Check(candidate[i])) answer.pb(candidate[i]);
        }

        for (auto ans : answer)
        {
            cout << ans << " ";
        }
        cout << '\n';
    }
}
