// URL: https://www.acmicpc.net/problem/2342
// Algo: DP

// Start:	240904 17 20
// Read:	0 1
// Think:	0 7
// Code:	0 22
// Total:	0 30

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) x.begin(), x.end()
#define pb push_back

constexpr int INF = 0x3f3f3f3f;

// 압축 풀이 2020KB 12ms
int dp[2][5][5]; 

int GetCost(int a, int b)
{
    if (a == b) return 1;
    if (a == 0) return 2;
    if ((a + b) % 2 == 1) return 3;
    return 4;
}

int main()
{
    fastio;
    memset(dp, INF, sizeof(dp));

    bool cur = 0;
    dp[cur][0][0] = 0;

    while (true)
    {
        int num;
        cin >> num;
        if (num == 0) break;
        cur = !cur;

        for (int i = 0; i < 5; ++i)
        {
            for (int j = 0; j < 5; ++j)
            {
                if (dp[!cur][i][j] == INF) continue;
                dp[cur][num][j] = min(dp[cur][num][j], dp[!cur][i][j] + GetCost(i, num));
                dp[cur][i][num] = min(dp[cur][i][num], dp[!cur][i][j] + GetCost(j, num));
                dp[!cur][i][j] = INF; // 다음 턴에 !cur이 cur이 되어 재활용하는만큼 INF로 초기화해준다
            }
        }
    }

    int answer = INF;
    for (int i = 0; i < 5; ++i)
    {
        for (int j = 0; j < 5; ++j)
        {
            answer = min(answer, dp[cur][i][j]);
        }
    }
    cout << answer;
}

// 정석 풀이 11.7MB 16ms
// int dp[100'001][5][5];
/*
int main()
{
    fastio;
    memset(dp, INF, sizeof(dp));
    dp[0][0][0] = 0;

    int cnt = 0;
    while (true)
    {
        int num;
        cin >> num;
        if (num == 0) break;
        ++cnt;

        for (int i = 0; i < 5; ++i)
        {
            for (int j = 0; j < 5; ++j)
            {
                if (dp[cnt - 1][i][j] == INF) continue;
                dp[cnt][num][j] = min(dp[cnt][num][j], dp[cnt - 1][i][j] + GetCost(i, num));
                dp[cnt][i][num] = min(dp[cnt][i][num], dp[cnt - 1][i][j] + GetCost(j, num));
            }
        }
    }

    int answer = INF;
    for (int i = 0; i < 5; ++i)
    {
        for (int j = 0; j < 5; ++j)
        {
            answer = min(answer, dp[cnt][i][j]);
        }
    }
    cout << answer;
}
*/
