// URL: https://school.programmers.co.kr/learn/courses/30/lessons/118669
// Algo: 다익스트라 변형

// Start:	240419 23 00
// Read:	0 5
// Think:	0 15
// Code:	0 30
// Total:	0 50
// 오모시로이

// 다익스트라에서 우선순위 큐에서 pop되는 노드가 '확정'된다는 기본 개념을 응용한 문제
// 문제가 복잡하게 써져있지만 그냥 출입구에서 산봉우리로 가는 최단 경로를 구하는 문제이고
// 최단 경로의 정의가 '거쳐가는 간선 중의 최대값'으로 바뀐다는 차이임.

// 처음엔 다익스트라를 모든 출발점마다 돌려야된다고 생각해서
// 시간복잡도가 안 된다고 판단해 DFS 방식으로 접근함.
// 산봉우리를 정답에 넣어야하니, 산봉우리들을 순회하며 출입구를 찾는 식으로 진행했다.

// 노드의 간선을 오름차순으로 정렬해서 그리디처럼 최소 비용 경로로 산봉우리를 찾을 떄까지 파고 들어가
// visited된 노드는 건너뛰며 완전 탐색하는 방식. 실패와 시간 초과 둘 다 뜸.
// 그리디답게 간선 최대값이 가장 작지 않은 경로로 산봉우리에 도달하게 되므로 틀린다.

// 다시 다익스트라 쪽으로 생각해서 '확정' 개념을 응용하는 걸 떠올림.
// 확정된 노드를 visited 배열로 체크하는 방식. DFS 방식과 로직 자체는 비슷하다.
// 정답이긴 하나 테케25에서 134ms로 느림

// 바킹독 해설을 보니 다익스트라를 1번만 돌려도 되는 문제였다.
// 다익스트라를 여러번 돌리면 시간초과가 날만한 최악 테케가 없는 문제였는듯.
// 50000개 노드가 각각 하나의 노드와 연결되어 있는데, 50000개 중 하나만 산봉우리고
// 나머지는 모두 출입구라면, 출입구에서 시작해서 50000개 간선씩 검사해서 산봉우리를 찾아야하니
// O(5만 x 5만 log 5만) 으로 터질만 했다.

// 문제 예시대로 출입구를 순회하며 산봉우리를 찾는 식으로 다시 바꾸고
// 다익스트라 시작 전에 출입구들을 몽땅 우선순위큐에 넣으면 된다.

// 이때 산봉우리의 D값은 업데이트하더라도, 산봉우리에서 출발하는 간선은 큐에 추가하지 않아
// 산봉우리를 지나는 경로는 찾지 않는다는게 중요

// 그러면 어떤 출입구에서 각 산봉우리까지 도달하는 최단 경로를 얻을 수 있고
// 산봉우리들을 순회해서 가장 작은 최단경로 값을 찾으면 정답이다.
// 테케25 53ms로 1/2배로 줄어듦

#include <algorithm>
#include <vector>
#include <queue>

using namespace std;
using pii = pair<int, int>;
constexpr int INF = 0x3f3f3f3f;

vector<int> solution(int n, vector<vector<int>> paths, vector<int> gates, vector<int> summits) {
    vector<bool> summit(n + 1);
    for (const int num : summits)
        summit[num] = true;
    
    vector<vector<pii>> adj(n + 1);
    for (const auto& path : paths)
    {
        adj[path[0]].push_back({path[2], path[1]});
        adj[path[1]].push_back({path[2], path[0]});
    }
    
    priority_queue<pii, vector<pii>, greater<>> pq; // {비용, 노드}
    vector<int> D(n + 1, INF);
    for (const int num : gates)
    {
        D[num] = 0;
        pq.push({0, num});
    }
    
    while (!pq.empty())
    {
        auto [cost, node] = pq.top(); pq.pop();
        if (D[node] != cost) continue;
        for (auto [nCost, nNode] : adj[node])
        {
            if (D[nNode] <= max(cost, nCost)) continue;
            D[nNode] = max(cost, nCost);
            if (!summit[nNode])
                pq.push({D[nNode], nNode});
        }
    }
    
    vector<int> answer{INF, INF}; // {출발, 비용}
    for (const int num : summits)
    {
        if (D[num] <= answer[1])
        {
            answer[0] = D[num] == answer[1] ? min(num, answer[0]) : num;
            answer[1] = D[num];
        }
    }

    return answer;
}


// 다익스트라 산봉우리들만큼 반복. 성공
/*
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;
using pii = pair<int, int>;
constexpr int INF = 0x3f3f3f3f;

vector<int> solution(int n, vector<vector<int>> paths, vector<int> gates, vector<int> summits) {
    vector<bool> gate(n + 1);
    for (const int num : gates)
        gate[num] = true;
    
    vector<int> visitedOrg(n + 1, false);
    for (const int num : summits)
        visitedOrg[num] = true;
    
    vector<vector<pii>> adj(n + 1);
    for (const auto& path : paths)
    {
        adj[path[0]].push_back({path[2], path[1]});
        adj[path[1]].push_back({path[2], path[0]});
    }
    
    vector<int> answer{INF, INF}; // {산등, 비용}
    for (const int k : summits)
    {
        auto visited = visitedOrg;
        visited[k] = false;
        
        priority_queue<pii, vector<pii>, greater<>> pq; // {비용, 노드}
        pq.push({0, k});
        
        while (!pq.empty())
        {
            auto [mx, node] = pq.top(); pq.pop();
            if (visited[node]) continue;
            visited[node] = true;
            
            if (gate[node])
            {
                if (mx <= answer[1])
                {
                    answer[0] = mx == answer[1] ? min(k, answer[0]) : k;
                    answer[1] = mx;
                }
                break;
            }
            
            for (auto [nMx, nNode] : adj[node])
            {
                pq.push({max(mx, nMx), nNode});
            }
        }
    }
    
    return answer;
}
*/

// DFS 실패
/*
#include <algorithm>
#include <vector>
#include <iostream>

using namespace std;
using pii = pair<int, int>;
constexpr int INF = 0x3f3f3f3f;

vector<int> solution(int n, vector<vector<int>> paths, vector<int> gates, vector<int> summits) {
    vector<bool> gate(n + 1);
    for (const int num : gates)
        gate[num] = true;
    
    sort(summits.begin(), summits.end());
    vector<bool> visitedOrg(n + 1);
    for (const int num : summits)
        visitedOrg[num] = true;
    
    vector<vector<pii>> adj(n + 1);
    for (const auto& path : paths)
    {
        adj[path[0]].push_back({path[2], path[1]});
        adj[path[1]].push_back({path[2], path[0]});
    }
    
    for (auto& tmp : adj)
        sort(tmp.begin(), tmp.end());
    
    vector<int> answer{-1, INF};
    for (const int k : summits)
    {
        auto visited = visitedOrg;
        
        auto DFS = [&](const auto& RE, int num, int mx) {
            visited[num] = true;
            if (gate[num])
            {
                if (mx < answer[1])
                {
                    answer[0] = k;
                    answer[1] = mx;
                }
                return;
            }

            for (const auto [cost, nxt] : adj[num])
                if (!visited[nxt])
                    RE(RE, nxt, max(mx, cost));
        };
    
        DFS(DFS, k, -1);
    }
    
    return answer;
}
*/