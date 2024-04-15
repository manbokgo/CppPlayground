// URL: https://school.programmers.co.kr/learn/courses/30/lessons/42884
// Algo: 그리디

// Start:	240415 21 20
// Read:	0 2
// Think:	0 10
// Code:	0 10 휴대폰 코딩
// Total:	0 22

#include <algorithm>
#include <vector>

constexpr int INF = 0x3f3f3f3f;
using namespace std;

int solution(vector<vector<int>> routes) {
    sort(routes.begin(), routes.end(), [](const auto& a, const auto& b) { return a[0] < b[0]; });
    
    int answer = 1;
    int mDist = INF;
    for (const auto& route : routes)
    {
        if (mDist < route[0])
        {
            ++answer;
            mDist = route[1];
        }
        else
        {
            mDist = min(mDist, route[1]);
        }
    }
    
    return answer;
}