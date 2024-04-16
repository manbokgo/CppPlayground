// URL: https://school.programmers.co.kr/learn/courses/30/lessons/17678
// Algo: 시뮬레이션

// Start:	240416 19 17
// Read:	0 5
// Think:	0 10
// Code:	1 2
// Total:	1 17

// 쓸데없이 코딩 실수 연발하면서 오래 걸림
// 1. 경우의 수를 제대로 파악 못함. 다 필요없고 막차만 중요한 거였다.
// 2. deque 써서 앞에 하나씩 빼면 될 것을, vector로 앞에꺼 빼지 않으려 하다보니
//    upper_bound 쓰면서 마지막 탑승객 반복자 갱신하는 식으로 쓸데없이 어렵게함
// 3. {시, 분} pii가 아니라 그냥 분으로 하면 될 걸 복잡하게 함(!!!)
// 4. 정답 출력 때 쓸 oss 스펙 잘 모름
//
// deque 떠올랐을 때 그냥 썼으면 시간 절반을 줄었을 듯. 수련이 더 필요하다.

#include <algorithm>
#include <deque>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>

using namespace std;
using pii = pair<int, int>;

string solution(int n, int t, int m, vector<string> timetable) {
    deque<int> crews;
    for (const string& crew : timetable)
    {
        int hr = stoi(crew.substr(0, 2));
        int mn = stoi(crew.substr(3));
        crews.push_back(hr * 60 + mn);
    }
    
    sort(crews.begin(), crews.end());

    int answer = 1500;
    int busCount = 0;
    int mn = 60 * 9;
    int transferred = 0;
    for (; busCount < n; ++busCount, mn += t)
    {
        for (transferred = 0; transferred < m; ++transferred)
        {
            if (crews.empty()) break;
            if (crews.front() > mn) break;
            answer = crews.front();
            crews.pop_front();
        }
    }
    mn -= t;

    if (busCount == n && transferred == m) // 막차가 꽉 찼으면, 막차에는 꼭 타야하니 막차 마지막 놈 1분 전에 선다.
        answer -= 1;
    else // 막차에 자리가 있으면, 막차 도착 시간에 탄다.
        answer = mn;

    ostringstream oss;
    oss << setw(2) << setfill('0') << answer / 60
        << ":"
        << setw(2) << setfill('0') << answer % 60;
    
    return oss.str();
}



// 제출 코드. 조금 멍청하게 했다.
/*
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iomanip>

using namespace std;
using pii = pair<int, int>;

pii MinusMn(pii time)
{
    auto [hr, min] = time;
    if (min == 0) return {hr - 1, 59};
    else return {hr, min - 1};
}

string solution(int n, int t, int m, vector<string> timetable) {
    vector<pii> crews;
    crews.reserve(timetable.size());
    for (const string& crew : timetable)
    {
        int hr = stoi(crew.substr(0, 2));
        int mn = stoi(crew.substr(3));
        crews.push_back({hr, mn});
    }
    
    sort(crews.begin(), crews.end());
    
    auto transfered = crews.begin();
    int hr = 9;
    int mn = -t;
    pii ans = {90, 90};
    for (int i = 0; i < n; ++i)
    {
        mn += t;
        while (mn >= 60)
        {
            mn -= 60;
            ++hr;
        }
        
        auto it = upper_bound(crews.begin(), crews.end(), pii{hr, mn});
        if (it - transfered >= m) 
        {
            pii tmpTime = {hr, mn};
            for (int j = 1; j < t; ++j)
            {
                tmpTime = MinusMn(tmpTime);
                it = upper_bound(crews.begin(), crews.end(), tmpTime);
                if (it - transfered < m)
                {
                    ans = tmpTime;
                    break;
                }
            }
            
            transfered += m;
        }
        else
        {
            ans = {hr, mn};
            transfered = it;
        }
    }
    
    if (transfered != crews.begin())
    {
        pii tmp = MinusMn(*(transfered - 1));
        if (ans.first == 90 ||
           (ans.first < tmp.first) ||
           (ans.first == tmp.first && ans.second < tmp.second)) 
            ans = tmp;
    }
    
    ostringstream oss;
    oss << setw(2) << setfill('0') << ans.first
        << ":"
        << setw(2) << setfill('0') << ans.second;
    
    return oss.str();
}
*/