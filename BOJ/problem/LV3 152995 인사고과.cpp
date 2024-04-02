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
    pii minA = {INF, INF};
    pii minB = {INF, INF};
    
    vector<pii> tmp, sums;
    tmp.reserve(scores.size());
    sums.reserve(scores.size());
    
    for (int i = 0; i < scores.size(); ++i)
    {
        const auto& score = scores[i];
        tmp.push_back({score[0], score[1]});
        sums.push_back({score[0] + score[1], i});
    }
    sort(sums.begin(), sums.end(), greater<>());
    
    sort(tmp.begin(), tmp.end(), [](const auto& a, const auto& b) { return a.first < b.first; });
    for (int i = 0; i < tmp.size(); ++i)
    {
        auto [a, b] = tmp[i];
        bool isMin = true;
        for (int j = i + 1; j < tmp.size(); ++j)
        {
            auto [na, nb] = tmp[j];
            if (a < na && b < nb)
            {
                isMin = false;
                i = j;
                break;
            }
        }
        
        if (isMin)
        {
            minA = tmp[i];
            break;
        }
    }
    
    sort(tmp.begin(), tmp.end(), [](const auto& a, const auto& b) { return a.second < b.second; });
    for (int i = 0; i < tmp.size(); ++i)
    {
        auto [a, b] = tmp[i];
        bool isMin = true;
        for (int j = i + 1; j < tmp.size(); ++j)
        {
            auto [na, nb] = tmp[j];
            if (b < nb && a < na)
            {
                isMin = false;
                i = j;
                break;
            }
        }
        
        if (isMin)
        {
            minB = tmp[i];
            break;
        }
    }
    
    cout << minA.first << ' ' << minA.second;
    cout << '\n';
    cout << minB.first << ' ' << minB.second;
    
    int answer = -1;
    int rank = 1;
    int removed = 0;
    int lastSum = INF;
    for (int i = 0; i < sums.size(); ++i)
    {
        auto [sum, idx] = sums[i];
        const auto& cur = scores[idx];
        bool noInsen = false;
        if ( (cur[0] < minA.first && cur[1] < minA.second)  ||
             (cur[0] < minB.first && cur[1] < minB.second)  )
        {
            noInsen = true;
            ++removed;
        }
            
        
        if (!noInsen && lastSum != sum)
        {
            rank = i + 1 - removed;
            lastSum = sum;
        }
        
        if (idx == 0)
        {
            answer = noInsen ? -1 : rank;
        }
    }
    
    return answer;
}