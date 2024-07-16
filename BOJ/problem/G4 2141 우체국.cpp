// URL: https://www.acmicpc.net/problem/2141
// Algo: 수학, 그리디 or 이분 탐색

// Start:	240716 12 21
// Read:	0 2
// Think:	0 57
// Code:	0 31
// Total:	1 30
// 패배
// 오모시로이

// 완전 탐색은 시간복잡도상 안 된다.

// 처음의 생각:
// 1. 러프하게 생각해서 -10억 위치와 5억 위치 마을 2개가 있을 때, 어느 것을 선택하든 다른 한 쪽은 15억만큼 곱해져야하므로
// 사람 수가 많은 마을을 선택하는 것이 최적이다.
// 2. 5억명 --- 10억명  사이에 5억명 마을이 있을 때, 이 마을이 왼쪽, 오른쪽 어느 쪽에 가깝든간에
// 여러 시나리오를 생각해봐도 이 마을을 선택하는 것이 최적이다.
// 정리하면 사람이 많이 밀집된 곳에 가까워질수록 계산값이 작아진다.

// mid 기준 왼쪽 구간 사람 수와 오른쪽 구간 사람 수가 비슷할수록 정답에 가까워진다고 생각했는데 틀렸다.
// 인덱스 번호 = 거리 라고 가정하고 반례를 몇 개 들자면

// 반례: (3, 3, 1, 5)
// idx 2의 계산값은 14, idx 3의 계산값도 14이므로 더 작은 인덱스인 2가 정답임
// 그런데 idx 3(값 1)이 왼쪽과 오른쪽의 사람 수 차가 가장 작은 경우다...

// 반례: (1000, 5, 5, 500) 처럼 왼쪽과 오른쪽 사람 수 차가 가장 작은건 idx 2이지만
// 정답은 idx 1인 경우도 있다.

// 결국 포기하고 해결법 찾아보니 '+mid를 포함한' 왼쪽 구간과, 오른쪽 구간의 차가 가장 작은 경우,
// 다시 말해 누적된 사람 총합/2 을 넘기는 순간의 지점이 정답인데
// 해설을 제대로 한 데가 단 한 군 데도! 없이 블로그에 무지성으로, 이유는 모르겠는데 이렇게 하면 암튼 풀림~ㅎ 하는 것밖에 없다. 화난다.

// 곰곰히 생각해보니 수학적으로 증명해야 하는 문제다.
// https://www.geogebra.org/calculator
// 그래프 그리는 사이트에서 확인해 봄. 계산값 f(x) = sigma (|x - 거리i| * 사람i) (1 <= i <= n) 임
// 예시: 1 10, 3 3, 4 5, 5 1
// abs(x-1)*10+abs(x-3)*3+abs(x-4)*5+abs(x-5)*1

// 일차함수고, 계산값의 최소가 거리1인 인덱스1임을 확인할 수 있고, 각 마을 위치인 1, 3, 4, 5에서 기울기가 변하는 걸 알 수 있다.
// |x - 거리i|의 값이 양수면 사람i는 기울기 +, 음수면 사람i는 기울기 -가 되어
// 위 경우 1~3 구간은 기울기가 1, 3~4 구간은 7이다.

// 기울기가 -였다가, +로 전환되는 지점이 극소점이므로
// 왼쪽 구간 사람의 합이(양수) 오른쪽 구간 사람의 합(음수)과 같아지거나 커지는 지점을 찾아야 한다는 것이다.



#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) x.begin(), x.end()
#define pb push_back

constexpr int INF = 0x3f3f3f3f;
using ll = long long;
using pii = pair<int, int>;

pii vills[100'001];
ll sum[100'001];

int main()
{
    fastio;

    int n;
    cin >> n;

    vills[0].first = -INF;
    for (int i = 1; i <= n; ++i)
    {
        auto& [a, b] = vills[i];
        cin >> a >> b;
    }
    sort(vills, vills + n + 1);

    // 그리디
    ll total = 0;
    for (int i = 1; i <= n; ++i) total += vills[i].second;
    const ll target = (total + 1) / 2;

    ll tmp = 0;
    for (int i = 1; i <= n; ++i)
    {
        tmp += vills[i].second;
        if (tmp >= target)
        {
            cout << vills[i].first;
            return 0;
        }
    }

    // 이분 탐색
    /*    
    for (int i = 1; i <= n; ++i)
        sum[i] = sum[i - 1] + vills[i].second;

    int lo = 1;
    int hi = n;
    while (lo < hi)
    {
        const int mid = (lo + hi) / 2;
        if (sum[mid] >= sum[n] - sum[mid]) hi = mid;
        else lo = mid + 1;
    }

    cout << vills[lo].first;
    */
}
