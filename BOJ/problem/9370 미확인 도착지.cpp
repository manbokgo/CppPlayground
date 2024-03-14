// URL: https://www.acmicpc.net/problem/9370
// Algo: 다익스트라

// Start:	240314 19 55
// Read:	0 2
// Think:	0 1
// Code:	0 16    전역변수 테케마다 초기화하는거 좀 잘하셈
// Code:	1 06    엄청난 바보짓으로 30분+30분 날림
// Total:	1 25

// 시간초과라길래 시간복잡도 문제인가하고 이것저것 시도하느라 30분 날림.
// 최단 경로가 여러개 가능한데도 한 최단경로만 저장해놓아서, 저장한 경로 속에서 mid1-mid2 간선을 못 찾으면 무한루프 돌아서 시간초과인 거 발견.

// 그래서 최단 경로 여러개를 저장할 수 있도록 pre를 vector 배열로 바뀌었는데 틀렸습니다 뜸.
// 왜 그런지 짱구만 굴리면서 30분 생각하면서 헤매다가, 직접 테스트케이스 하나 만들어서 디버깅해보니
// 108번줄 if (d[nNode] > d[node] + nCost) 상황에서 기존 pre를 날려야 한다는 점을 이제야! 깨닫고 정답.
// d[nNode] == d[node] + nCost일때만 pre에 pb해서 여러 최단 경로를 저장하는 거다.

// 앞으론 머릿 속에서 테스트케이스 시뮬 돌리지말고 직접 넣어서 확인해볼 것. 제발.
// THINK MARK THINK!!

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
