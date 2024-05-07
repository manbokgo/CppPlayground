// URL: https://school.programmers.co.kr/learn/courses/30/lessons/150367
// Algo: 구현, DFS

// Start:	240507 22 42
// Read:	0 4
// Think:	0 15
// Code:	0 46
// Total:	1 5

// 포화이진트리의 높이를 dep라고 하면, 노드의 개수 cnt는 (2^dep)-1개고,
// cnt는 비트 수를 의미하니 최대 표현할 수 있는 수의 범위는 2^cnt까지임

// 아래 방법을 쓸려면 이렇게 어떤 값을 표현할 수 있는 최대 비트 수를 구해서
// 문제 예시와 같이 리딩 제로가 붙은듯이 간주해야 함

// 문제와 같이 중위 순회를 하면, 전체 비트의 가운데 비트가 자기 자신을 의미하고
// 왼쪽 구간의 가운데가 왼쪽 자식, 오른쪽 구간의 가운데가 오른쪽 자식을 의미한다. 재귀한다.
// 자식이 존재하는데, 자신(부모)이 없다면 유효하지 않으므로 return false;

// 로직 자체는 그나마 금방 떠올렸는데, long long 타입 관련해서 엄청 헤맸다...

// 1. ll과 비교할 값도 ll이어야 한다. 1<<cnt가 아니라 1LL<<cnt여야 함.
// 그냥 1<<cnt하면 int 타입이 되니 int 범위로 표현되며 오버플로됨. 멍청함.

// 2. ll 최댓값 범위 넘기는 걸 주의해야 함.
// dep가 6일때 cnt는 63이 되는데, 1LL<<63는 long long의 음수 최솟값이 되므로 무한 루프 돌게 됨
// num <= (1LL<<63)-1 로 양수 최대값(2^63 - 1)을 의미하도록 고쳐야한다.
// 그냥 dep이 6이면 종료하도록 조건 수정해서 고침

#include <vector>

using ll = long long;
using namespace std;

bool check(int left, int right, ll num)
{
    if (left == right) return true;
    
    int mid = (left + right) / 2;
    bool cur = num & 1LL << mid;
    bool lChild = num & 1LL << (left + mid-1) / 2;
    bool rChild = num & 1LL << (mid+1 + right) / 2;
    
    if ( (lChild || rChild) && !cur) return false;
    
    return ( check(left, mid-1, num) &&
             check(mid+1, right, num) );
}

vector<int> solution(vector<ll> numbers) {
    vector<int> answer;
    answer.reserve(numbers.size());
    for (const ll num : numbers)
    {
        // dep ?  cnt (2^dep)-1  max 2^cnt
        int dep = 1;
        int cnt = (1 << dep) - 1;
        while (dep < 6) {
            if (num < 1LL<<cnt) break;
            ++dep;
            cnt = (1 << dep) - 1;
        }
        
        answer.push_back(check(0, cnt - 1, num));
    }

    return answer;
}
