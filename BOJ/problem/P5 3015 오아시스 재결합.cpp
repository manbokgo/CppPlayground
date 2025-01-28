// URL: https://www.acmicpc.net/problem/3015
// Algo: 스택

// Start:	250129 06 00
// Read:	0 1
// Think:	0 17
// Code:	0 10
// Total:	0 28

// P5 6549 히스토그램에서 가장 큰 직사각형 문제와 비슷하다.

// 만약 값들에 중복 없었다면:
// 스택이 내림차순이 되도록 넣어주게 되며, 스택 속에 있는 값들은 왼쪽으로 쌍이 이미 맺어진 상태다.
// 만약 num이 top()보다 더 크다면, 스택 속 num보다 작은 값들은 더 이상 오른쪽 너머를 볼 수 없으므로
// pop을 해주며 ++ans로 num과의 쌍을 센다.
// 이후 스택이 비어있지 않다면, top()과 num을 연결하는 쌍을 하나 더 세준다.

// 그러나 이 문제에서는 값들이 중복으로 나올 수 있는데
// num과 중복된 값들은 아직 오른쪽 너머를 볼 수 있으므로 중복 값이라면 pop을 한 것을 다시 넣어줘야 한다.
// 하지만 위 방식에서 pop한 것을 다시 일일이 넣어주는 과정을 추가하면 중복 값이 많은 저격 케이스에서 바로 시간초과다.

// 중복 개수 cnt를 스택에 같이 저장해주고 ++ans 대신 +=cnt를 해주는 식으로 바꾼다.
// 이후 {num, cnt}로 스택에 넣어주면 pop, push 연산을 줄여 최적화할 수 있다.

// https://blog.thecloer.com/121

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) x.begin(), x.end()
#define pb push_back

using pii = pair<int, int>;
using ll = long long;

int main()
{
    fastio;

    int n;
    cin >> n;

    stack<pii> S; // {값, 개수}

    ll ans = 0;
    while (n--)
    {
        int num;
        cin >> num;

        int cnt = 1;
        while (!S.empty() && S.top().first <= num)
        {
            ans += S.top().second;
            if (S.top().first == num) cnt += S.top().second;
            S.pop();
        }
        if (!S.empty()) ++ans;
        S.push({num, cnt});
    }
    cout << ans;
}
