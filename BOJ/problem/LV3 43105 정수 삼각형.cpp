// URL: https://school.programmers.co.kr/learn/courses/30/lessons/43105
// Algo: 그리디

// Start:	240409 20 20
// Read:	0 1
// Think:	0 7
// Code:	0 3
// Total:	0 11

// 아래에서 위로 가며 큰 값 더하는 방식으로 간단하게 풀 수 있다.
// 알고리즘 분류 DP인거 보니깐 위에서 아래로 가며 DP로 푸는게 의도인거 같은데 굳이?

#include <string>
#include <vector>

using namespace std;

int solution(vector<vector<int>> tri) {
    for (int i = tri.size() - 1; i >= 1; --i)
    {
        auto& prv = tri[i-1];
        const auto& lst = tri[i];
        for (int j = 0; j < lst.size() - 1; ++j)
        {
            prv[j] += max(lst[j], lst[j + 1]);
        }
    }

    return tri[0][0];
}