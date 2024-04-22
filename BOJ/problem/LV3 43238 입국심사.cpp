// URL: https://school.programmers.co.kr/learn/courses/30/lessons/43238
// Algo: 이분 탐색, 매개변수 탐색

// Start:	240423 00 24
// Read:	0 2
// Think:	0 3
// Code:	0 3
// Total:	0 8

#include <vector>

using namespace std;
using ll = long long;

ll solution(int n, vector<int> times) {
    ll st = 1;
    ll en = 1e18;
    while (st < en)
    {
        ll mid = (st + en) / 2;
        
        ll count = 0;
        for (auto time : times)
            count += mid / time;
        
        if (count >= n) en = mid;
        else st = mid + 1;
    }
    
    return st;
}