// URL: https://school.programmers.co.kr/learn/courses/30/lessons/92343
// Algo: 비트마스킹, BFS (DFS)

// Start:	240408 22 11
// Read:	0 1
// Think:	0 12
// Code:	0 17
// Total:	0 30
// 오모시로이

// 백트래킹으로 하면 {0, 1, 2}를 검사하는 경우가 중복으로 생긴다.
// 시간 복잡도는 정확히 계산하기는 힘들지만 굉장히 러프하게 17! 정도로 시간 초과 가능성
// (정작 문제 채점 테케가 미흡해서 백트래킹으로도 정답 처리된다)

// 위의 {0, 1, 2} 경우처럼 어떤 집합의 검사는 한번만 해도 된다는 점이 핵심.
// 모든 부분 집합을 비트마스킹 state로 만들어 visited로 체크한다. 최대 2^17 = 131072개의 집합 검사이므로 가능하다.

// queue를 사용해 BFS로 풀었는데, DFS 재귀가 로직은 동일한데 코드가 더 깔끔한 듯
// 바킹독 해설이랑 거의 똑같은 생각 흐름으로 풀었다. 캬~

#include <queue>
#include <vector>

using namespace std;

int solution(vector<int> info, vector<vector<int>> edges) {
    const int n = info.size();
    
    vector<int> left(n, -1);
    vector<int> right(n, -1);
    for (const auto& edge : edges)
    {
        int p = edge[0];
        int c = edge[1];
        
        if (left[p] == -1) left[p] = c;
        else right[p] = c;
    }
    
    vector<bool> visited(1 << n); // 실수: 사이즈가 (1<<n)여야지 인덱스 (1<<n)-1까지 접근 가능
    queue<int> q;
    q.push(1);
    
    int answer = 0;
    while (!q.empty())
    {
        int mask = q.front();
        q.pop();
        
        if (visited[mask]) continue;
        visited[mask] = true;
        
        int sheep = 0;
        int wolf = 0;
        for (int i = 0; i < n; ++i)
        {
            if (mask & (1 << i))
            {
                if (info[i]) ++wolf;
                else ++sheep;
            }
        }
        
        if (wolf >= sheep) continue;
        answer = max(answer, sheep);
        
        for (int i = 0; i < n; ++i)
        {
            if (mask & (1 << i))
            {
                if (left[i] != -1) q.push(mask | (1 << left[i]));
                if (right[i] != -1) q.push(mask | (1 << right[i]));
            }
        }
        
    }
    
    return answer;
}