// URL: https://school.programmers.co.kr/learn/courses/30/lessons/68646
// Algo: 구현

// Start:	240326 21 48
// Read:	0 2
// Think:	0 7
// Code:	0 8
// Total:	0 17

// min(X왼쪽구간) < X < min(X오른쪽구간)를 성립하면 최후까지 남을 수 있다
// 전체 배열의 최소값을 찾은 후 맨왼쪽에서부터 최소값까지, 맨오른쪽에서부터 최소값까지
// 순차적으로 접근하여 위 조건에 맞는 X 개수를 센다.
// 최소값 찾기 O(n), 전체 순회 O(n)으로 시간 복잡도 O(n)

#include <bits/stdc++.h>
using namespace std;

constexpr int INF = 0x3f3f3f3f;

int solution(vector<int> a) {
    int answer = 1;
    int minIdx = min_element(a.begin(), a.end()) - a.begin();
    
    int left = INF;
    for (int i = 0; i < minIdx; ++i)
    {
        if (left > a[i]) ++answer;
        left = min(left, a[i]);
    }
    
    int right = INF;
    for (int i = a.size() - 1; i > minIdx; --i)
    {
        if (right > a[i]) ++answer;
        right = min(right, a[i]);
    }
    
    return answer;
}