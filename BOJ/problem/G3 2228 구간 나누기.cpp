// URL: https://www.acmicpc.net/problem/2228
// Algo: DP

// Start:	240713 14 45
// Read:	0 2
// Think:	0 12
// Code:	0 23
// Total:	0 37

// dp[cnt][i]  1~i에서 cnt개의 구간들의 최대 합

// 1. 1~i-1에서 cnt개의 최대 합과
// 2. i에서 시작하는 j가 --되며 역순회로 누적 합을 구한 것 + 1~j-2에서 cnt-1개의 최대 합
// 을 비교하여 큰 것으로 dp[cnt][i]를 구한다

// cnt의 이전값과, cnt-1의 이전값을 동시에 참조해야 하는만큼 DP 배열의 압축은 귀찮은 일임.

// 만약 j-1 인덱스 접근이었다면 0 인덱스를 패딩으로 넣는 1-Based 인덱스로 깔끔하게 되지만
// 구간들이 인접하면 안 된다는 규칙에 따라 j-2 인덱스를 접근하는 것 때문에 2-Based 인덱스를 써야하는데
// 이러면 오히려 더 헷갈릴테니 바텀 업에서 지저분하게 조건문 나눌 수 밖에 없었다.

// 이런 경우는 탑다운이 깔끔한 듯


#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) x.begin(), x.end()
#define pb push_back

constexpr int INF = 0x3f3f3f3f;

int n, m;
int dp[51][101];
int arr[101];

int Solve(int cnt, int i)
{
    if (cnt == 0) return 0;
    if (i <= 0) return -INF;
    if (dp[cnt][i] != INF) return dp[cnt][i];

    int sum = 0;
    dp[cnt][i] = Solve(cnt, i - 1);
    for (int j = i; j > 0; --j)
    {
        sum += arr[j];
        dp[cnt][i] = max(dp[cnt][i], Solve(cnt - 1, j - 2) + sum);
    }

    return dp[cnt][i];
}

int main()
{
    fastio;
    cin >> n >> m;

    for (int i = 1; i <= n; ++i)
        cin >> arr[i];


    // 탑다운
    memset(dp, INF, sizeof(dp));
    cout << Solve(m, n);

    // 바텀업
    /*
    for (int cnt = 1; cnt <= m; ++cnt)
        dp[cnt][0] = -INF;

    for (int cnt = 1; cnt <= m; ++cnt)
    {
        for (int i = 1; i <= n; ++i)
        {
            dp[cnt][i] = dp[cnt][i - 1];

            int sum = 0;
            if (cnt == 1)
            {
                for (int j = i; j > 0; --j)
                {
                    sum += arr[j];
                    dp[cnt][i] = max(dp[cnt][i], sum);
                }
            }
            else
            {
                for (int j = i; j > 2; --j)
                {
                    sum += arr[j];
                    dp[cnt][i] = max(dp[cnt][i], dp[cnt - 1][j - 2] + sum);
                }
            }
        }
    }
    cout << dp[m][n];
    */
}
