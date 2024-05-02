// URL: https://school.programmers.co.kr/learn/courses/30/lessons/118668
// Algo: DP, 완전 탐색

// Start:	240502 22 12
// Read:	0 2
// Think:	0 43
// Code:	0 18
// Total:	1 1

// 너무 어렵게 생각했다. 40분 동안 온갖 잡생각을 다 했다.
// 각 문제의 알고력,코딩력의 시간당 효율을 구하고 내가 필요한 알고력,코딩력 가중치를 곱해서 최선의 선택을 그리디하는 거나...
// DP 풀이로 2번째 문제 가능까지의 최소 시간을 DP에 넣으려면 정직하게 헤딩, 0번쨰 문제 거치고 뺑뺑이, 1번째 문제 거치고 뺑뺑이 중에 최소값...
// 암만 생각해봐도 반례가 계속 떠올라서 코딩 완전정지하고 헤맴.

// 이 정도 되니 내가 너무 어렵게 생각하는 건가? 하고 뇌 세척하고 문제 찬찬히 다시 읽어보니
// 그냥 완전 탐색 3중 루프 돌아도 n은 150이니 충분히 가능함. 아... 아.....!

// 이미 '도달까지의 최소 시간'이라는 개념을 잡생각에서 떠올라서 DP로 풀어야하는 거 바로 알아챔
// problems에 헤딩 방법을 더미로 넣는 것도 잡생각하면서 떠올라서 했는데
// 바킹독 센세 풀이보다 코드가 더 깔끔한 걸 보니 뿌듯한 걸?
// alpMax와 copMax 초기값을 각각 alp, cop로 줘야하는 걸 놓치고 7분 헤맨거 빼면 수월하게 품

#include <vector>
#include <cstring>

using namespace std;

int dp[151][151];

// 0 필요a
// 1 필요c
// 2 보상a
// 3 보상c
// 4 시간

int solution(const int alp, const int cop, vector<vector<int>> problems) {
    memset(dp, 0x3f, sizeof(dp));
    int alpMax = alp, copMax = cop;
    for (const auto& prob : problems)
    {
        alpMax = max(alpMax, prob[0]);
        copMax = max(copMax, prob[1]);
    }
    problems.push_back({0,0,1,0,1});
    problems.push_back({0,0,0,1,1});

    dp[alp][cop] = 0;
    for (int i = alp; i <= alpMax; ++i)
    {
        for (int j = cop; j <= copMax; ++j)
        {
            for (const auto& prob : problems)
            {
                if (i < prob[0] || j < prob[1]) continue;

                int nAlp = min(i + prob[2], alpMax);
                int nCop = min(j + prob[3], copMax);
                dp[nAlp][nCop] = min(dp[nAlp][nCop], dp[i][j] + prob[4]);
            }
        }
    }

    return dp[alpMax][copMax];
}