// URL: https://school.programmers.co.kr/learn/courses/30/lessons/12987
// Algo: 구현

// Start:	240425 20 48
// Read:	0 2
// Think:	0 3
// Code:	0 10 폰코딩
// Total:	0 15

// "set는 신이야!"하는 채팅 언뜻 보고는 set로 풀어야하는 문제인가? 싶어서 생각해보니
// set 쓰면 정렬 안 해도 되네? 하고 풀었는데 멍청했다.

// 정렬 O(n log n)인데, set는 삽입삭제 O(log n)을 2n번 하니 그게 그거고,
// 게다가 set는 lower_bound O(log n)로 접근해야 하는데, 정렬한 배열의 접근 O(1)보다 당연히 느리다.
// 효율성 테스트 시간 4배 느리게 나옴. 확증 편향에 빠졌다!

// 이상하게 안 하고 정공법으로 정렬해서 풀면 아주 심플한 문제임.

#include <algorithm>
#include <vector>

using namespace std;

int solution(vector<int> A, vector<int> B) {
    sort(A.begin(), A.end());
    sort(B.begin(), B.end());
    int i = 0;
    for (int j = 0; j <B.size(); ++j)
      if (A[i] < B[j])
          ++i;
    return i;
}

// multiset 풀이
/*
#include <vector>
#include <set>

using namespace std;

int solution(vector<int> A, vector<int> B) {
    multiset<int> S(B.begin(), B.end());
    int answer = 0;
    for (const int num : A) {
        if (auto it = S.upper_bound(num); it != S.end()) {
            ++answer;
            S.erase(it);
        }
    }
    return answer;
}
*/