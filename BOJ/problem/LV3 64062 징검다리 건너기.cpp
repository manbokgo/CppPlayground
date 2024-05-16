// URL: https://school.programmers.co.kr/learn/courses/30/lessons/64062
// Algo: 이분 탐색 + 매개변수 탐색 or 슬라이딩 윈도우 Maximum

// Start:	240429 02 02
// Read:	0 1
// Think:	0 3
// Code:	0 3
// Total:	0 7
// 오모시로이

// 지금까지 매개변수 탐색 문제는 대부분 FFFFTTTT, 조건 만족시 mid 값을 줄여야 하는 경우였는데
// 이 문제는 반대로 TTTTFFFF, 조건 만족시 mid 값을 늘려야하는 경우라서 mid = (st+en+1)/2; 으로 해야함
// 이분 탐색을 좀 더 확실히 개념 잡은 듯

// 이분 탐색 풀이 O(n log n)로 금방 풀었지만, 알고 보니 O(n) 풀이도 가능한데 이게 좀 재미있다
// Sliding Window Maximum 라는 유명한 문제와 이 문제가 개념적으로 동일한데
// 길이가 k인 모든 슬라이딩 윈도우 속 최댓값 들의 최솟값(x)이 정답이 된다.

// x를 모든 값에 빼도, 모든 슬라이딩 윈도우는 0 이상인 값을 최소 하나 가지게 되며
// 음수 값이 이전 사람으로 인해 박살난 돌을 의미한다.
// 경우의 수를 고려해보면 연속된 음수의 길이가 최대 k-1이니 x번째 사람까지는 충분히 건널 수 있다. 오.

// 이 풀이를 효율적으로 구현하는 방법은 Deque를 사용한다.

// 1. Deque의 뒤에서부터 원소를 집어넣는다.
// 2. Deque의 앞 원소가 지금 집어넣을 원소에서 왼쪽으로 k 범위 안에 없다면, pop_front()
// 3. Deque의 뒷 원소가 지금 집어넣을 원소보다 작다면, pop_back()
// 4. Deque의 앞 원소가 현재 슬라이딩 윈도우의 최댓값이다. (단, 현재 인덱스 >= k-1)

// 1,2는 당연한 내용이고, 슬라이딩 윈도우의 최댓값을 구하는 것만이 중요한만큼
// 3를 통해 현재 윈도우에서 최댓값이 아닌 원소는 싹 버리고, 최댓값이 항상 앞 원소로 위치하도록 하여
// 4로 빠르게 최댓값에 접근할 수 있다. 신박함.

// https://velog.io/@rmswjdtn/%EC%8A%AC%EB%9D%BC%EC%9D%B4%EB%94%A9-%EC%9C%88%EB%8F%84%EC%9A%B0-Leet-code-239.-Sliding-Window-Maximum
// https://school.programmers.co.kr/questions/41064


// 슬라이딩 윈도우 풀이
#include <vector>
#include <deque>

using namespace std;
using pii = pair<int, int>;
constexpr int INF = 0x3f3f3f3f;

int solution(vector<int> stones, int k) {
    deque<pii> dq; // {값, 인덱스}
    int answer = INF;
    for (int i = 0; i < stones.size(); ++i)
    {
        while (!dq.empty() && dq.front().second < i - k + 1) dq.pop_front();
        while (!dq.empty() && dq.back().first < stones[i]) dq.pop_back();
        dq.push_back({stones[i], i});
        if (i >= k-1 && dq.front().first < answer) answer = dq.front().first;
    }
    return answer;
}


/*
// 이분 탐색 풀이
#include <vector>

using namespace std;

int solution(vector<int> stones, int k) {
    int st = 0;
    int en = 200'000'000;
    
    while (st < en)
    {
        int mid = (st + en + 1) / 2;

        bool check = true;
        int cur = 0;
        for (const int stone : stones)
        {
            if (stone < mid)
            {
                ++cur;
                if (cur >= k)
                {
                    check = false;
                    break;
                }
            }
            else
            {
                cur = 0;
            }
        }
        
        if (check) st = mid;
        else en = mid - 1;
    }
    
    return st;
}
*/