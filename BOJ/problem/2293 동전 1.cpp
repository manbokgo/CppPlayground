// URL: https://www.acmicpc.net/problem/2293
// Algo: DP 기본

// Start:	240210 23 00 
// Read:	0 0
// Think:	0 10
// Code:	0 10
// Total:	0 20

#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define X first
#define Y second
#define all(x) x.begin(), x.end()
#define sortvec(x) sort(all(x))
#define compress(x) x.erase(unique(all(x)), x.end())
#define findvec(x, value) find(all(x), value) != x.end()

using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;

constexpr ll  MOD = 1000000007;
constexpr int INF = 0x3f3f3f3f;
constexpr ll  LLINF = 1e18;

int dp[10005];
int n, k;
int coin[105];

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> k;
    for (int i = 1; i <= n; ++i)
    {
        cin >> coin[i];
    }


    // 1~i번째 동전을 사용하여 k를 만들 수 있는 경우의 수
    // i 순회하며 dp 덮채우기
    // i번째 동전을 하나도 사용하지 않은 기존 경우의 수 (=k원을 1~i-1번쨰 동전으로 채우는 경우의 수)
    // + i번쨰 동전을 하나 사용하는 경우 (=나머지 k-coin[i]원을 1~i번째 동전으로 채우는 경우의 수)

    // i번째 동전을 하나 (이상) 사용해야지만 기존 dp값(1~i-1번째 동전만 사용)하는 경우와 차별이 생겨서
    // 경우의 수가 새로 유의미하게 생김

    // bottom-up
    dp[0] = 1;
    for (int i = 1; i <= n; ++i)
    {
        // j가 coin[i] 미만일시 'i번쨰 동전을 하나 사용하는 경우'가 아예 0이므로 갱신 안 함 
        for (int j = coin[i]; j <= k; ++j) // 실수: j가 k '이하'까지 <=
        {
            dp[j] += dp[j - coin[i]];
        }
    }

    // top-down 불가능?
    // dp[k][n] 2차원 배열로 두고, 'i번쨰 동전을 하나 사용하는 경우'로만 채우는 것이 근본 접근.
    // dp[j][i] = dp[j-coin[i]][i] + dp[j-coin[i]][i-1] + ... + dp[j-coin[i]][1]
    // 최종 답은 dp[k]의 모든 [n]의 합 (본 문제라면 dp[10][1] = 1, dp[10][2] = 5, dp[10][3] = 4)
    // 이 방식을 사용할시 탑다운 재귀로 가능할 것 같으나
    // n 100, k 10000 으로 dp 배열만 4MB로 메모리 초과로 인해 불가능.
    // dp를 채워넣을 떄나, 최종 답을 낼 때 결국 dp[k]의 모든 [n]의 합이 필요하기 때문에
    // 아예 누적 합으로 dp를 채우는 식으로 1차원 배열로 압축 가능함.

    cout << dp[k];
}
