// URL: https://school.programmers.co.kr/learn/courses/30/lessons/12907
// Algo: DP

// Start:	240429 23 51
// Read:	0 1
// Think:	0 1
// Code:	0 8
// Total:	0 10

// 예전에 푼 백준 G5 동전 1 문제랑 동일한 문제임. 복습.


#include <cstring>
#include <vector>

using namespace std;
constexpr int MOD = 1'000'000'007;
int dp[100'001];

int solution(int n, vector<int> money) {
    dp[0] = 1;
    for (int i = 0; i < money.size(); ++i)
        for (int j = money[i]; j <= n; ++j)
            dp[j] += dp[j - money[i]] % MOD;

    return dp[n] % MOD;
}


// 궁금해서 해본 탑다운 dp. 재귀 호출이 너무 많아서 정확성 테케도 20ms이고 효율성은 시간 초과
/*
#include <cstring>
#include <vector>

using namespace std;
constexpr int MOD = 1'000'000'007;
int dp[101][100'001];

int DFS(int i, int n, const vector<int>& m)
{
    if (dp[i][n] != -1) return dp[i][n];
    dp[i][n] = DFS(i-1, n, m) % MOD;
    if (n >= m[i-1]) dp[i][n] += DFS(i, n - m[i-1], m) % MOD;
    return dp[i][n];
}

int solution(int n, vector<int> money) {
    memset(dp, -1, sizeof(dp));
    for (int i = 1; i <= n; ++i) dp[0][i] = 0;
    dp[0][0] = 1;
    return DFS(money.size(), n, money) % MOD;
}
