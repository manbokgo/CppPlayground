// URL: https://school.programmers.co.kr/learn/courses/30/lessons/131129
// Algo: DP, 논리

// Start:	240509 17 51
// Read:	0 3
// Think:	0 46
// Code:	0 16
// Total:	1 5

// 처음엔 60 쭉 뺀 거와 50 쭉 뺀거를 비교하는 그리디 식으로 접근해서 틀림
// 곰곰히 생각해보니 60을 어느정도 빼다가 50을 빼야 최적인 반례가 있어서
// dp로 풀어야겠다고 생각이 듦. 근데 정확히 어떻게 해야할지 방법 찾기가 매우 힘들었음.

// 310 이전까지는 50, 60 둘 중 어느 것을 우선시로 빼서 B값이 큰지는 따져봐야하지만  60*5 + 10, 50*5 + 60
// 310 이후로는 무조건 60을 빼는게 C 최단임. 따라서 310 전까지만 dp를 채우는데
// 1~60까지는 수동으로 넣고, 61~310은 50+a와 60+a 중에 최단인 것을 dp로 넣는 식이다.
// 타겟 값이 310 이하가 될 때까지 60을 계속 빼다가 dp 값과 더하면 정답.

// 102처럼 60 빼기가 아니라 51*2 로 되는 경우도 있지만
// 60*1 + 42 도 어차피 C2 B0으로 동일하니 60+a 경우만 따지면 됨

#include <vector>

using namespace std;
using pii = pair<int, int>;

vector<int> solution(int target) {
    vector<pii> dp(311);
    for (int i = 1; i <= 20; ++i)
        dp[i] = {1, 1};
    
    for (int i = 21; i <= 60; ++i)
    {
        if (i % 2 == 0 && i / 2 <= 20) dp[i] = {1, 0};
        else if (i % 3 == 0 && i / 3 <= 20) dp[i] = {1, 0};
        else if (i <= 40) dp[i] = {2, 2};
        else if (i > 50) dp[i] = {2, 2};
        else dp[i] = {2, 1};
    }
    dp[50] = {1,1};
    
    for (int i = 61; i <= 310; ++i)
    {
        auto& [C, B] = dp[i];
        auto [c50, b50] = dp[i-50];
        auto [c60, b60] = dp[i-60];
        if (c50 <= c60)
        {
            C = c50 + 1;
            B = b50 + 1;
        }
        else
        {
            C = c60 + 1;
            B = b60;
        }
    }
    
    int cnt = 0;
    while (target > 310)
    {
        ++cnt;
        target -= 60;
    }
    
    return {dp[target].first + cnt, dp[target].second};
}