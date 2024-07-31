// URL: https://school.programmers.co.kr/learn/courses/30/lessons/12920
// Algo: 이분 탐색, 매개변수 탐색

// Start:	240508 18 06
// Read:	0 2
// Think:	0 6
// Code:	0 13
// Total:	0 21

#include <vector>

using namespace std;
constexpr int MAX = 50'000;

int solution(int n, vector<int> cores) {
    int st = 1;
    int en = 500'000'000;
    while (st < en)
    {
        const int mid = (st + en) / 2;
        
        int cnt = 0;
        for (int i = 0; i < cores.size(); ++i)
        {
            cnt += mid / cores[i] + 1;
            if (cnt > MAX) cnt = MAX;
        }
        
        if (cnt < n) st = mid + 1;
        else en = mid;
    }
    
    int cnt = 0;
    for (int i = 0; i < cores.size(); ++i)
    {
        cnt += (st - 1) / cores[i] + 1;
    }

    for (int i = 0; i < cores.size(); ++i)
    {
        if (st % cores[i] == 0)
        {
            ++cnt;
            if (cnt == n) return i + 1;
        }
    }
    
    return -1;
}