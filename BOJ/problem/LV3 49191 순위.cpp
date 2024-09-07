// URL: https://school.programmers.co.kr/learn/courses/30/lessons/49191
// Algo: 플로이드

// Start:	240404 19 58
// Read:	0 1
// Think:	0 5
// Code:	0 8
// Total:   0 14

// G3 1516 게임 개발과 비슷하게, 위상 정렬부터 떠올랐는데
// '정확하게 순위를 매길 수 있는 선수의 수'는 이 방법으로 불가능함

// 플로이드로 해서 바로 품. 확실히 갈 수 있는 경로만 true로 두고, false는 알 수 없는 상태를 의미함.
// 타겟 노드 k와 다른 노드 i가 있을 때
// A. arr[i][k] 노드i에서 타겟으로 갈 수 있거나
// B. !arr[i][k] 노드i에서 타겟으로 가는 건 알 수 없지만, arr[k][i] 타겟에서 노드i로 갈 수 있다면
// 모든 노드i가 둘 중 하나를 만족하면 타겟은 정확하게 순위를 매길 수 있다.
// 따라서 검출 조건은 if (!arr[i][k] && !arr[k][i]) found = false;

#include <string>
#include <vector>

using namespace std;

int solution(int n, vector<vector<int>> results) {
    vector<vector<bool>> arr(n + 1, vector<bool>(n + 1, false));
    for (const auto& result : results)
    {
        arr[result[0]][result[1]] = true;
    }
    
    for (int k = 1; k <= n; ++k)
    {
        arr[k][k] = true;
        for (int i = 1; i <= n; ++i)
        {
            for (int j = 1; j <= n; ++j)
            {
                if (arr[i][k] && arr[k][j]) arr[i][j] = true;
            }
        }
    }
    
    int answer = 0;
    for (int k = 1; k <= n; ++k)
    {
        bool found = true;
        for (int i = 1; i <= n; ++i)
        {
            if (!arr[i][k] && !arr[k][i])
            {
                found = false;
                break;
            }
        }
        
        if (found) ++answer;
    }
    
    
    return answer;
}