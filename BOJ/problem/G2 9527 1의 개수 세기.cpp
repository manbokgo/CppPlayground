// URL: https://www.acmicpc.net/problem/9527
// Algo: 수학, DP(누적 합), 비트마스킹

// Start:	240922 11 33
// Read:	0 1
// Think:	0 26
// Code:	0 18
// Total:	0 45
// 오모시로이

// 20은 이진수로 10100
// 20 & 16 을 만족한 후, 0xxxx 꼴에서 x에서 나오게 되는 모든 1의 수를 더한다.

// 1xxxx 꼴에서 맨앞의 1이 반복되는 횟수는 뒤가 000 001 010 011 100일 때로 총 5회다.
// 맨앞에 1이 나온 상태로 진행할 숫자가 20-16=4만큼 남았는데, 정확히 숫자가 16이라서 뒤가 000인 경우도 세야하니
// 20-16+1=5회로 계산하게 된다. 간단히 정리하면 16 + 0~4의 개수만큼 반복된다.

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) x.begin(), x.end()
#define pb push_back

using ll = long long;

ll dp[55]; // log2(10^16) = 53.15... = 54번째 자리까지 가능하다

ll Solve(ll num)
{
    ll cnt = 0;
    for (int i = 55; i >= 1; --i)
    {
        if (num & (1LL << (i - 1))) // i번째 자리가 1인지 확인
        {
            cnt += dp[i - 1] + 1;  // 0xxxx에서 나오게 되는 1의 수
            num -= (1LL << (i - 1));
            cnt += num + 1; // 맨 앞의 1이 반복되는 수
        }
    }
    return cnt;
}

int main()
{
    fastio;

    dp[0] = 0;
    dp[1] = 1;
    dp[2] = 4;
    for (int i = 3; i <= 55; ++i)
    {
        // 0xxxx, 1xxxx 에서 x에 들어가는 모든 1의 수는 각각 dp[i-1]로 구한다.
        // 맨 앞의 1이 반복되는 횟수는 xxxx의 모든 경우의 수 = 2^4 이므로 더해준다.
        dp[i] = 2 * dp[i - 1] + (1LL << (i - 1));
    }

    ll a, b;
    cin >> a >> b;
    cout << Solve(b) - Solve(a - 1LL);
}
