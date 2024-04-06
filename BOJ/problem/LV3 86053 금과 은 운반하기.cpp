// URL: https://school.programmers.co.kr/learn/courses/30/lessons/86053
// Algo: 이분 탐색 (매개변수 탐색)

// Start:	240406 17 47
// Read:	0 2
// Think:	1 0
// Code:	0 10
// Total:	1 12
// 오모시로이
// 패배

// 필요 시간에 대하여 이분 탐색(매개변수 탐색)로 풀어야겠다고 생각은 금방 들었는데
// 어떻게 하면 check() 함수를 구현해야 하는지에서 막힘. 결국 정답 봄.
// a+b <= total 조건을 떠오르지 못했다. 금과 은을 크게 '자원'이라고 보고 유동적으로 비율 조절된다는 점을 파고들었어야함.

// 벡터를 활용한 증명은 [노션 그림] 참조.
// T라는 시간 동안 최대 옮길 수 있는 자원 W는, 가로축 금, 세로축 은인 그래프에서
// 금 우선배달과 은 우선배달 각각에서 나오는 2개의 (금,은) 운송량 점을 연결하는 기울기가 -1인 선분으로 나타난다
// 이 선분에 -(a,b)를 했을 때, 선분이 1사분면을 지나면(축 포함)
// T 시간 동안 a, b만큼을 옮기고도 1사분면의 값만큼 더 운송 여력이 있다는 의미이므로 true인 경우다.

// 금 우선배달 때의 최대 금 운송량 gMax와 은 우선배달 때의 최대 은 운송량 sMax,
// 시간 동안 운송 가능한 최대 자원량 total을 구하고,
// 이는 a <= gMax && b <= sMax && a+b <= total 으로 체크 가능.

// 직관적인 증명은 일단 a와 b가 각각 gMax, sMax 이하여야지만 당연히 가능성이 있는 것이고
// a+b가 total 이하라면 a만큼의 금을 보내고, b만큼의 은을 보낸 후에도 더 운송 여력이 있다는 것이므로 true다.
// (만약 a+b가 total 초과라는 것은 a만큼의 금을 보내고, b만큼 은을 보낼 여력이 없다는 뜻)

// 도시 개수가 n, en의 값(최대 5e14)를 T라고 할 때 시간 복잡도는 O(n log T)

#include <algorithm>
#include <vector>

using namespace std;
using ll = long long;

bool check(ll time, int a, int b,
           const vector<int>& g, const vector<int>& s, const vector<int>& w, const vector<int>& t)
{
    ll gMax = 0, sMax = 0, total = 0;
    for (int i = 0; i < g.size(); ++i)
    {
        ll count = time / t[i];
        count -= count / 2;

        ll avail = w[i] * count;
        gMax += min((ll)g[i], avail);
        sMax += min((ll)s[i], avail);
        total += min((ll)g[i] + s[i], avail);
    }
    
    return a <= gMax && b <= sMax && a+b <= total;
}

ll solution(int a, int b, vector<int> g, vector<int> s, vector<int> w, vector<int> t) {
    ll st = 0;
    ll en = 5e14;

    while (st < en)
    {
        ll mid = (st + en) / 2;
        if (check(mid, a, b, g, s, w, t)) en = mid;
        else st = mid + 1;
    }
    
    return st;
}