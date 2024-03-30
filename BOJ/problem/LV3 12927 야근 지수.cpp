// URL: https://school.programmers.co.kr/learn/courses/30/lessons/12927
// Algo: 그리디

// Start:	240330 23 45
// Read:	0 1
// Think:	0 2
// Code:	0 22 실패
// Code:	0 07 
// Total:	0 32

// 첫 풀이는 전체적으로 빼주는 식으로 접근했는데 틀림. 중요한 건 최대값을 최대한 깎아내는 것이니 애초에 접근을 잘못했다.

// 문제 보자마자 떠올렸던 우선순위 큐로 n번 삽입/삭제하며 1씩 빼주는 방법이
// 시간 복잡도가 안 될 줄 알았는데 다시 생각해보니 충분히 된다. 생각 좀 잘하자. 후...
// 삽입/삭제 O(n log m)이고, 최종값 출력에 O(m log m)이니 시간 복잡도는 O(n+m log m)

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

long long solution(int n, vector<int> works) {
    priority_queue<int> pq(works.begin(), works.end());
    
    while (n)
    {
        int num = pq.top();
        if (!num) return 0;
        pq.pop();

        --n;
        pq.push(--num);
    }

    long long answer = 0;
    while (!pq.empty())
    {
        int num = pq.top();
        if (!num) break;
        pq.pop();

        answer += num * num;
    }

    return answer;
}


// 너무 어렵게 생각하지 마!
/*
long long solution(int n, vector<int> works) {
    sort(works.begin(), works.end(), greater<>());
    
    while (n)
    {
        auto it = lower_bound(works.begin(), works.end(), 0, greater<>());
        int count = it - works.begin();
        if (!count) break;

        int offCount = n % count;
        int offset = n / count;
        
        for (int i = 0; i < count; ++i)
        {
            int& num = works[i];
            if (num - offset >= 0)
            {
                n -= offset;
                num -= offset;
                if (offCount && num >= 1)
                {
                    n -= 1;
                    num -= 1;
                    offCount -= 1;
                }
            }
            else
            {
                n -= num;
                num = 0;
            }
        }
    }
    
    long long answer = 0;
    for (int num : works)
    {
        answer += num * num;
    }
        
    return answer;
}
*/
