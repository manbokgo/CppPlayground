// URL: https://www.acmicpc.net/problem/1562
// Algo: DP, 비트마스킹

// Start:	240719 14 26
// Read:	0 1
// Think:	0 22
// Code:	0 13
// Total:	0 36

// 비트마스킹을 각 자릿수의 유무로 판단해 1<<10 개가 필요하다고 생각해서 풀었는데,
// 인접한 숫자들로만 채워지는만큼, 0과 9가 존재한다면 1~8 또한 존재한다는 것을 의미하기 때문에
// 0과 9의 유무만 판단하는 1<<2 = 4 크기로만으로도 충분하다.

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) x.begin(), x.end()
#define pb push_back

using ll = long long;
constexpr ll MOD = 1'000'000'000;

ll dp[101][10][4]; // n, 마지막수, 비트마스크
// 0: X
// 1: 0 존재
// 2: 9 존재
// 3: 0,9 존재

int main()
{
    fastio;

    int n;
    cin >> n;
    if (n < 10)
    {
        cout << 0;
        return 0;
    }

    for (int lst = 1; lst <= 8; ++lst) dp[1][lst][0] = 1;
    dp[1][9][2] = 1;

    for (int i = 2; i <= n; ++i)
    {
        for (int lst = 0; lst < 10; ++lst)
        {
            for (int mask = 0; mask < 4; ++mask)
            {
                if (dp[i - 1][lst][mask] == 0) continue;

                if (lst < 9)
                    dp[i][lst + 1][mask | (lst + 1 == 9 ? 2 : 0)] += dp[i - 1][lst][mask] % MOD;

                if (lst > 0)
                    dp[i][lst - 1][mask | (lst - 1 == 0 ? 1 : 0)] += dp[i - 1][lst][mask] % MOD;
            }
        }
    }

    ll answer = 0;
    for (int lst = 0; lst < 10; ++lst)
        answer += dp[n][lst][3] % MOD;

    cout << answer % MOD;
}
