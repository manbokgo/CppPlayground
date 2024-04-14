// URL: https://school.programmers.co.kr/learn/courses/30/lessons/81303
// Algo: 연결 리스트

// Start:	240415 02 42
// Read:	0 2
// Think:	0 11  삽입삭제하는 걸 보니 연결 리스트 먼저 떠올랐지만 뭔가 더 효율적이게 짤 수 있을 거 같음...! (바보임)
// Code:	0 15  map 풀이 실패. 로직 자체가 글러먹음.
// Code:	0 10  std::list 복구 위치 찾을 수가 없어서 포기. lower_bound는 선형 시간이니 의미 없음.
// Code:	0 5   set 풀이 효율성 실패
// Think:	0 9   삽입삭제 O(log n)을 엄청하나 보다... O(1)인 list로 돌아와서 erase하지 않는 커스텀 list 써야할 듯
// Code:	0 36  vector<Node> 만들고 보니 val는 그냥 인덱스고 prv, nxt만 바꾸니 깔끔히 vector prv, nxt로 변경. Z 복구 이상하게 생각해서 헤멤..
// Total:	1 28

#include <string>
#include <vector>
#include <stack>

using namespace std;

string solution(int n, int k, vector<string> cmds) {
    vector<int> prv;
    vector<int> nxt;
    stack<int> S;
    
    prv.reserve(n);
    nxt.reserve(n);
    for (int i = 0; i < n; ++i)
    {
        prv.push_back(i - 1);
        nxt.push_back(i + 1);
    }
    
    for (const auto& str : cmds)
    {
        if (str[0] == 'U' || str[0] == 'D')
        {
            int X = stoi(str.substr(2));
            if (str[0] == 'U') { while(X--) k = prv[k]; }
            else { while(X--) k = nxt[k]; }
        }
        else if (str[0] == 'C')
        {
            S.push(k);
            if (prv[k] != -1) nxt[prv[k]] = nxt[k];
            if (nxt[k] != n) prv[nxt[k]] = prv[k];
            
            if (nxt[k] == n) k = prv[k];
            else k = nxt[k];
        }
        else if (str[0] == 'Z')
        {
            int num = S.top(); S.pop();
            
            // 스택이니깐 복잡하게 생각할 거 없었다..
            if (prv[num] != -1) nxt[prv[num]] = num;
            if (nxt[num] != n) prv[nxt[num]] = num;
        }
    }
    
    string answer;
    answer.resize(n, 'O');
    while (!S.empty())
    {
        int num = S.top(); S.pop();
        answer[num] = 'X';
    }
    
    return answer;
}


// set 효율성 실패
/*
#include <string>
#include <vector>
#include <set>
#include <stack>
#include <iostream>

using namespace std;

string solution(int n, int k, vector<string> cmds) {
    set<int> ST;
    stack<int> S;
    
    for (int i = 0; i < n; ++i) ST.insert(i);
    auto cur = ST.find(k);
    
    for(const auto& str : cmds)
    {
        if (str[0] == 'U' || str[0] == 'D')
        {
            int X = stoi(str.substr(2));
            if (str[0] == 'U') { while(X--) --cur; }
            else { while(X--) ++cur; }
        }
        else if (str[0] == 'C')
        {
            S.push(*cur);
            cur = ST.erase(cur);
            if (cur == ST.end()) --cur;
        }
        else if (str[0] == 'Z')
        {
            int num = S.top();
            S.pop();
            
            ST.insert(num);
        }
    }
    
    string answer;
    answer.resize(n, 'X');
    for (auto num : ST) answer[num] = 'O';
    
    return answer;
}
*/


// map 실패. 다시 생각해보니 로직 자체가 답이 없다.
/*
#include <string>
#include <vector>
#include <map>
#include <stack>
#include <iostream>

using namespace std;

string solution(int n, int k, vector<string> cmds) {
    map<int, int> M;
    stack<int> S;
    
    int deleted = 0;
    for(const auto& str : cmds)
    {
        if (str[0] == 'U' || str[0] == 'D')
        {
            int X = stoi(str.substr(2));
            if (str[0] == 'U') X = -X;
            k += X;
        }
        else if (str[0] == 'C')
        {
            S.push(k);
            ++M[k];
            ++deleted;
            if (k == n - deleted) --k;
        }
        else if (str[0] == 'Z')
        {
            int num = S.top();
            S.pop();
            
            auto it = M.find(num);
            --it->second;
            if (it->second == 0) M.erase(it);
            --deleted;
            if (num <= k) ++k;
        }
    }
    
    string answer;
    answer.reserve(n);
    
    int idx = 0;
    int totalD = 0;
    for (auto it = M.begin(); it != M.end(); ++it)
    {
        auto [num, deCount] = *it;
        for (int i = 0; i < num - totalD - idx; ++i) answer.push_back('O');
        for (int i = 0; i < deCount; ++i) answer.push_back('X');
        idx = num;
        totalD += deCount;
    }
    
    for (int count = answer.size(); count < n; ++count) answer.push_back('O');
    
    return answer;
}
*/