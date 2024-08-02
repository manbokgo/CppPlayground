// URL: https://www.acmicpc.net/problem/7579
// Algo: DP (0-1 배낭 문제)

// Start:	240802 09 52
// Read:	0 2
// Think:	0 16
// Code:	0 8
// Total:	0 26

// 다 풀고나서 보니 전형적인 배낭 문제인데 굉장히 헷갈렸음.
// 배낭 문제의 핵심은 비용(무게)의 한계가 주어졌을 때, 가치를 최대화하는 것이다. (*)

// 비용별 최대 가치를 쭉 찾아내고, 비용이 작은 것부터 쭉 순회하며 최대 가치가 m 이상인 것을 찾으면 정답이다.

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) x.begin(), x.end()
#define pb push_back

int w[101]; // 비용. 비활성화 비용.
int v[101]; // 가치. 비활성화하여 얻는 메모리.
int dp[10'001];

int main()
{
    fastio;

    int n, m;
    cin >> n >> m;

    for (int i = 1; i <= n; ++i)
        cin >> v[i];

    int k = 0;
    for (int i = 1; i <= n; ++i)
    {
        cin >> w[i];
        k += w[i];
    }
        

    for (int i = 1; i <= n; ++i)
    {
        for (int j = k; j >= w[i]; --j)
        {
            dp[j] = max(dp[j], v[i] + dp[j - w[i]]);
        }
    }

    for (int i = 0; i <= k; ++i)
    {
        if (dp[i] >= m)
        {
            cout << i;
            return 0;
        }
    }
}
