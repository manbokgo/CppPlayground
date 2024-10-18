// URL: https://www.acmicpc.net/problem/1720
// Algo: DP

// Start:	241018 06 39
// Read:	0 1
// Think:	0 6
// Code:	0 4
// Total:	0 11

// dp에 존재하는 경우는 크게 2가지로 나뉠 수 있다.  dp[n] = 1번 + 2번
// 1. 자체적으로 좌우 대칭
// 2. 자체적으로 좌우 대칭 X

// 이 때 2번은 좌우대칭시 중복된 표현이므로 1/2을 하여 답을 구해야 한다.
// 따라서 정답은 1번 + 2번/2 인데 이 식을 변형하면  (dp[n] + 1번) / 2  라고 할 수 있다.

// 즉, 1번 경우의 수를 구하는 게 중요하다.

// 만약 n이 홀수라면 정가운데에 1x2 타일이 존재하고, (n-1)/2 크기의 좌우 구간에 좌우대칭 타일들이 존재하는 경우이므로
// 경우의 수는 dp[(n-1) / 2]이다.

// 만약 n이 짝수라면 정확히 절반을 나누는 경우(dp[n/2]) +
// 정가운데에 2x1 타일 2개가 존재하는 경우(dp[n/2-1]) + 2x2 타일이 존재하는 경우(dp[n/2-1])  이므로
// 경우의 수는 dp[n / 2] + dp[n / 2 - 1] * 2 이다.

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) x.begin(), x.end()
#define pb push_back

int dp[31];

int main()
{
    fastio;

    int n;
    cin >> n;

    dp[0] = 1;
    dp[1] = 1;
    for (int i = 2; i <= n; ++i)
        dp[i] = dp[i - 1] + dp[i - 2] * 2;

    if (n % 2 == 1) // 홀수
        cout << (dp[n] + dp[(n - 1) / 2]) / 2;
    else // 짝수
        cout << (dp[n] + dp[n / 2] + dp[n / 2 - 1] * 2) / 2;
}
