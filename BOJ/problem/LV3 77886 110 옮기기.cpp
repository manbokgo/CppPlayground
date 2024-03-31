// URL: https://school.programmers.co.kr/learn/courses/30/lessons/77886
// Algo: 그리디

// Start:	240401 01 42
// Read:	0 2
// Think:	0 12
// Code:	0 47
// Total:	1 1

// 구현이 왜 이렇게 까다로움.. 많이 헤맸다.

// 110은 접두사와 접미사가 겹치지 않는 단어이므로 그리디하게 보이는 족족 추출해도 다른 110과 공유하는 일이 없어서 괜찮다
// 반대 예시: 만약 접두사와 접미사가 겹치는 101 이었다면 "101011"에서 앞부터 추출하면 1개밖에 추출 못하지만 뒤부터 추출하면 최대인 2개다.

// 기본적으로 110 보다 사전 순으로 뒤에 있는건 111 뿐이니 111을 찾아서 그 앞에 110을 붙여주면 됨
// 처음엔 111이 없다면 그냥 뒤에 붙이면 된다고 생각했지만, 그냥 '1'만 남았을 때는 앞에 붙여야하는 점 보고 다시 생각함
// '10101'를 생각해보니 뒤에서부터 순회해서 처음 나오는 0 위치 다음에(만약 0이 없다면 맨앞에) 삽입하면 된다는 점 깨달음

// 처음엔 인덱스로 접근하는 풀이를 이상하게 했다가
// (마지막에서 2번째 글자를 tmp[sz-3]로 그때 그때 확인하면 될 걸 루프 돌면서 c3 변수를 매번 업데이트하는 식으로 멍청하게 함)
// 예외처리가 너무 많아 스택으로 넣고 빼면서 검사하고 다시 넣고 하는 식으로 꺾음
// 제출해서 정답 나오긴 했는데 채점 시간이 무슨 2000ms 나오는 케이스 있는 거 보고 기함함
// 다른 사람 풀이 보니 처음대로 인덱스 접근이 깔끔한 거였다. 다시 짰더니 만족스러운 성능 나옴

#include <bits/stdc++.h>
using namespace std;

vector<string> solution(vector<string> s) {
    vector<string> answer;
    answer.reserve(s.size());
    
    for (const auto& str : s)
    {
        string tmp;
        string ans;
        tmp.reserve(str.size());
        ans.reserve(str.size());
        
        int count = 0;
        for (char c : str)
        {
            tmp += c;
            int sz = tmp.size();
            if (sz < 3) continue;

            if (tmp[sz-3] == '1' && tmp[sz-2] == '1' && tmp[sz-1] == '0')
            {
                ++count;
                tmp.pop_back();
                tmp.pop_back();
                tmp.pop_back();
            }
        }

        /*
        int target = 0;
        for (int i = tmp.size() - 1; i >= 0; --i)
        {
            if (tmp[i] == '0')
            {
                target = i + 1;
                break;
            }
        }
        */
        int target = tmp.find_last_of('0') + 1; // 못 찾으면 npos(= -1)가 나오므로 +1 하면 의도한대로 0이 됨
        
        ans += tmp.substr(0, target);
        while (--count >= 0) ans += "110";
        ans += tmp.substr(target);

        answer.push_back(std::move(ans));
    }
    
    return answer;
}


// 정답이긴한데 굉장히 비효율적
/*
vector<string> solution(vector<string> s) {
    vector<string> answer;
    answer.reserve(s.size());
    
    for (const auto& str : s)
    {
        int count = 0;
        stack<char> S;
        for (auto c : str)
        {
            S.push(c);
            if (S.size() < 3) continue;
            
            char c1 = S.top();
            if (c1 != '0')
            {
                continue;
            }
            S.pop();
            
            char c2 = S.top();
            if (c2 != '1')
            {
                S.push(c1);
                continue;
            }
            S.pop();
            
            char c3 = S.top();
            if (c3 != '1')
            {
                S.push(c2);
                S.push(c1);
                continue;
            }
            S.pop();
            
            ++count;
        }
        
        
        string tmp;
        tmp.reserve(str.size());
        
        int target = 0;
        int sz = S.size();
        while (!S.empty())
        {
            char c = S.top();
            S.pop();
            
            if (target == 0 && c == '0')
            {
                target = sz;
            }
            
            tmp.push_back(c);
            --sz;
        }
        reverse(tmp.begin(), tmp.end());
        
        while (--count >= 0)
            tmp.insert(target, "110");
        
        answer.push_back(move(tmp));
    }
    
    return answer;
}*/


// 인덱스를 다루는 쪽이 맞았으나 방식이 멍청했음
/*
vector<string> solution(vector<string> s) {
    vector<string> answer;
    answer.reserve(s.size());
    
    for (const auto& str : s)
    {
        string tmp;
        tmp.reserve(str.size());
        
        int count = 0;
        char c1 = '\0';
        char c2 = '\0';
        char c3 = '\0';
        for (auto c : str)
        {
            c3 = c2;
            c2 = c1;
            c1 = c;
            
            if (c3 == '1' && c2 == '1' && c1 == '0')
            {
                ++count;
                tmp.pop_back();
                tmp.pop_back();

                int sz = tmp.size();
                c2 = tmp[sz - 2];
                c1 = tmp[sz - 1];
                continue;
            }
            
            tmp += c;
        }
        
        for (int i = 0; i < (int)tmp.size() - 2; ++i)
        {
            if (tmp[i] == '1' && tmp[i+1] == '1' && tmp[i+2] == '1')
            {
                while (count--)
                    tmp.insert(i, "110");
                break;
            }
        }
        
        while (--count >= 0)
            tmp.insert(tmp.size(), "110");
        
        
        answer.push_back(move(tmp));
    }
    
    return answer;
}
*/


int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<string> s {"1110", "100111100", "0111111010"};
    solution(s);
}
