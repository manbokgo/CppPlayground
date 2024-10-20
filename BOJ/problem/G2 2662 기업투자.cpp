// URL: https://www.acmicpc.net/problem/2662
// Algo: DP (0-1 배낭 문제 변형)

// Start:	241020 08 30
// Read:	0 1
// Think:	0 27
// Code:	0 18
// Total:	0 46
// 오모시로이

// 한 기업당 한 번만 돈을 투자할 수 있는 조건이기 때문에 변형이 필요하다.
// 1차원 DP를 사용하는 풀이 방식대로 하면 한 기업에 여러 번 투자할 수 있기 때문에 불가능하고
// 전형적인 2차원 DP 방식으로 접근한다.

// 각 기업에 얼마씩 투자했는지 복원하는게 까다로웠다.
// dp[i][k]가 최대값으로 갱신될 때 i번째 회사의 투자금액 w를 알 수 있는데,
// 이때 투자금은 dp[i-1][k-w] 상황에서 넣는 것인만큼, 이 상황에서 i-1번째 회사의 투자금액은 dp[i-1][k-w]이다.
// 이를 반복하여 각 기업별 투자금을 추적하면 된다.

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) x.begin(), x.end()
#define pb push_back

int company[21][301];
int dp[21][301]; // i번째 회사까지 사용할 때, k원으로 얻을 수 있는 최대 이익
int path[21][301]; // dp[i][k]가 최대값으로 갱신될 때의 i번째 회사의 투자금액

int main()
{
    fastio;

    int k, m;
    cin >> k >> m;

    for (int i = 1; i <= k; ++i)
    {
        int weight;
        cin >> weight;

        for (int j = 1; j <= m; ++j)
            cin >> company[j][weight];
    }

    for (int cIdx = 1; cIdx <= m; ++cIdx)
    {
        for (int w = 0; w <= k; ++w) // w를 0부터 시작하면 dp[cIdx][j] = dp[cIdx - 1][j] 효과가 있다
        {
            for (int j = k; j >= w; --j)
            {
                const int newVal = company[cIdx][w] + dp[cIdx - 1][j - w];
                if (dp[cIdx][j] < newVal)
                {
                    dp[cIdx][j] = newVal;
                    path[cIdx][j] = w;
                }
            }
        }
    }

    cout << dp[m][k] << '\n';

    vector<int> answer(m + 1);
    for (int cur = m, money = k; cur > 0; --cur)
    {
        answer[cur] = path[cur][money];
        money -= path[cur][money];
    }

    for (int i = 1; i <= m; ++i)
    {
        cout << answer[i] << ' ';
    }
}
