// URL: https://school.programmers.co.kr/learn/courses/30/lessons/12979
// Algo: 구현

// Start:	240505 22 36
// Read:	0 2
// Think:	0 5
// Code:	0 9
// Total:	0 16

#include <vector>
using namespace std;

int solution(int n, vector<int> stations, int w)
{
    stations.push_back(n + w + 1);
    const int sz = w * 2 + 1;
    
    int answer = 0;
    int cur = 1;
    for (const int pos : stations)
    {
        int frnt = pos - w;
        if (cur < frnt) {
            answer += (frnt - cur) / sz;
            if ((frnt - cur) % sz) ++answer;   
        }
        cur = pos + w + 1;
    }

    return answer;
}