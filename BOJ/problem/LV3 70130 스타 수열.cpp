// URL: https://school.programmers.co.kr/learn/courses/30/lessons/70130
// Algo: 그리디

// Start:	240506 22 30
// Read:	0 3
// Think:	0 8
// Code:	0 34
// Total:	0 45

// 50만 크기 배열(2MB)을 따로 만들고 싶지 않아서, 인자로 들어오는 a 배열을 sort 하는 방향으로 접근했는데
// 결국엔 이래도 각 요소별 인덱스를 추가해야 해서, pii 새로 선언하고 정렬하는 바람에 메모리 쓰는 양은 똑같은데
// 오히려 정렬 비용 + 캐시 미스 때문에 62ms로 더 느림

// 그냥 50만 크기 배열 2개 선언하고(마지막 위치, 덩어리 개수), 로직은 동일하게 하되
// 처음부터 쭉 순회하는 식으로 바꾸니 6ms로 아주 빨라짐
// 진작에 이렇게 할 걸. 프로그래머스에서는 메모리 아끼려는 태도 자체가 잘못된 듯.

#include <algorithm>
#include <vector>

using namespace std;

int solution(vector<int> a) {
    vector<int> lastPos(a.size() + 1, -1);
    vector<int> cnt(a.size() + 1);
    
    for (int i = 0; i < a.size(); ++i)
    {
        int num = a[i];
        if (i - lastPos[num] > 1) {
            ++cnt[num];
            lastPos[num] = i;
        }
        else if (i + 1 < a.size() && num != a[i+1]) {
            ++cnt[num];
            lastPos[num] = i + 1;
        }
        else {
            lastPos[num] = i;
        }
    }
    
    int answer = 0;
    for(int i = 0; i < cnt.size(); ++i)
        answer = max(answer, cnt[i]);

    return answer * 2;
}


// 정렬 풀이
/*
#include <algorithm>
#include <vector>

using namespace std;
using pii = pair<int, int>;

int solution(vector<int> a) {
    const int n = a.size();
    vector<pii> nums;
    nums.reserve(n);
    for (int i = 0; i < n; ++i)
        nums.push_back({a[i], i});
                 
    sort(nums.begin(), nums.end());
    
    int answer = 0;
    int count = 0;
    int lastIdx = -1;
    for (int i = 0; i < n; ++i)
    {
        auto [val, idx] = nums[i];
        if (idx-1 != lastIdx && idx-1 >= 0 && val != a[idx-1])
            lastIdx = idx - 1;
        else if (idx+1 != lastIdx && idx+1 <= n-1 && val != a[idx+1])
            lastIdx = idx + 1;
        else
            lastIdx = -1;
        
        if (lastIdx != -1)
            ++count;
        
        if (nums[i].first != nums[i+1].first)
        {
            answer = max(answer, count * 2);
            count = 0;
            lastIdx = -1;
        }
    }
    return answer;
}
*/