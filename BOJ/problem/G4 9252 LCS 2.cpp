// URL: https://www.acmicpc.net/problem/9252
// Algo: DP (LCS 기본)

// Start:	240312 18 36
// Read:	0 0
// Think:	0 1
// Code:	0 9
// Total:	0 10

// https://velog.io/@emplam27/%EC%95%8C%EA%B3%A0%EB%A6%AC%EC%A6%98-%EA%B7%B8%EB%A6%BC%EC%9C%BC%EB%A1%9C-%EC%95%8C%EC%95%84%EB%B3%B4%EB%8A%94-LCS-%EC%95%8C%EA%B3%A0%EB%A6%AC%EC%A6%98-Longest-Common-Substring%EC%99%80-Longest-Common-Subsequence

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) x.begin(), x.end()
#define pb push_back

string LCS(const string& a, const string& b)
{
    const int mxSz = (int)max(a.size(), b.size()) + 1;
    vector<vector<int>> dp(mxSz, vector<int>(mxSz));

    for (int i = 1; i <= (int)a.size(); ++i)
    {
        for (int j = 1; j <= (int)b.size(); ++j)
        {
            if (a[i - 1] == b[j - 1])
                dp[i][j] = dp[i - 1][j - 1] + 1;
            else
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
        }
    }

    if (dp[a.size()][b.size()] == 0) return {};

    string ret;
    for (int i = (int)a.length(), j = (int)b.length();;)
    {
        const int cur = dp[i][j];
        if (cur == 0) break;

        if (cur == dp[i - 1][j]) { --i; }
        else if (cur == dp[i][j - 1]) { --j; }
        else
        {
            ret.pb(a[i - 1]);
            --i;
            --j;
        }
    }
    reverse(all(ret));

    return ret;
}


int main()
{
    fastio;

    string aStr, bStr;
    cin >> aStr >> bStr;

    const string answer = LCS(aStr, bStr);
    cout << answer.size() << '\n' << answer;
}
