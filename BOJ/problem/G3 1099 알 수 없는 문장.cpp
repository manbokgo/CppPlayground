// URL: https://www.acmicpc.net/problem/1099
// Algo: DP

// Start:	241104 20 00
// Read:	0 1
// Think:	0 15
// Code:	0 24
// Total:	0 40

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) x.begin(), x.end()
#define pb push_back

constexpr int INF = 0x3f3f3f3f;

int dp[51]; // dp[i] = str[0..i]의 최소 비용
int cnt[51][26];

int main()
{
    fastio;
    memset(dp, INF, sizeof(dp));

    string str;
    cin >> str;

    int n;
    cin >> n;

    vector<string> words(n);
    for (int i = 0; i < n; ++i)
    {
        cin >> words[i];
        for (const char c : words[i])
            ++cnt[i][c - 'a'];
    }

    dp[0] = 0;
    for (int i = 1; i <= str.size(); ++i)
    {
        int nCnt[26]{};
        for (int j = i - 1; j >= 0; --j)
        {
            ++nCnt[str[j] - 'a'];
            for (int wIdx = 0; wIdx < n; ++wIdx)
            {
                if (i - j != words[wIdx].size()) continue;

                bool hasAll = true;
                for (int k = 0; k < 26; ++k)
                {
                    if (nCnt[k] != cnt[wIdx][k])
                    {
                        hasAll = false;
                        break;
                    }
                }
                if (!hasAll) continue;

                int cost = 0;
                for (int k = j; k < i; ++k)
                {
                    if (words[wIdx][k - j] != str[k]) ++cost;
                }
                dp[i] = min(dp[i], dp[j] + cost);
            }
        }
    }

    if (dp[str.size()] == INF) cout << -1;
    else cout << dp[str.size()];
}
