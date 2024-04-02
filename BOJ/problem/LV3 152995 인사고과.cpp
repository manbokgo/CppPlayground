// URL: https://school.programmers.co.kr/learn/courses/30/lessons/152995
// Algo: 

// Start:	240402 18 02
// Read:	0 1
// Think:	0 2
// Code:	0 15 일부 테케 실패
// Code:	0 25 또 실패..
// Total:	

#include <bits/stdc++.h>

using namespace std;
using pii = pair<int, int>;
constexpr int INF = 0x3f3f3f3f;

int solution(vector<vector<int>> scores) {
    vector<pii> sums;
    sums.reserve(scores.size());
    
    for (int i = 0; i < scores.size(); ++i)
    {
        const auto& score = scores[i];
        sums.push_back({score[0] + score[1], i});
    }
    
    sort(sums.begin(), sums.end(), greater<>());
    
    int rank = 1;
    int minAIdx = 0;
    int minBIdx = 0;
    for (int i = 0; i < sums.size(); ++i)
    {
        auto [sum, idx] = sums[i];
        const auto& cur = scores[idx];
        const auto& minA = scores[sums[minAIdx].second];
        const auto& minB = scores[sums[minBIdx].second];
        
        bool noInsen = false;
        if ( (cur[0] < minA[0] && cur[1] < minA[1])  ||
             (cur[0] < minB[0] && cur[1] < minB[1])  )
            noInsen = true;
        
        if (!noInsen)
        {
            if ( (cur[0] < minA[0]) || (cur[0] == minA[0] && cur[1] < minA[1]) ) minAIdx = i;
            if ( (cur[1] < minB[1]) || (cur[1] == minB[1] && cur[0] < minB[0]) ) minBIdx = i;
            
            if (i > 0 && sums[i-1].first != sum)
                rank = i + 1; 
        }
        
        if (idx == 0)
        {
            return noInsen ? -1 : rank;
        }
    }
}