// URL: https://www.acmicpc.net/problem/1958
// Algo: DP (LCS 변형)

// Start:	241103 18 50
// Read:	0 1
// Think:	0 1
// Code:	0 16
// Total:	0 18

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) x.begin(), x.end()
#define pb push_back

int LCSOnlySize(const string& a, const string& b, const string& c)
{
    const int mxSz = (int)max({a.size(), b.size(), c.size()}) + 1;
    vector dp(mxSz, vector(mxSz, vector<int>(mxSz)));

    for (int i = 0; i <= (int)a.size(); ++i)
    {
        for (int j = 0; j <= (int)b.size(); ++j)
        {
            for (int k = 0; k <= (int)c.size(); ++k)
            {
                if (i == 0 || j == 0 || k == 0)
                    dp[i][j][k] = 0;
                else if (a[i - 1] == b[j - 1] && b[j - 1] == c[k - 1])
                    dp[i][j][k] = dp[i - 1][j - 1][k - 1] + 1;
                else
                    dp[i][j][k] = max({dp[i - 1][j][k], dp[i][j - 1][k], dp[i][j][k - 1]});
            }
        }
    }

    return dp[a.size()][b.size()][c.size()];
}


int main()
{
    fastio;

    string aStr, bStr, cStr;
    cin >> aStr >> bStr >> cStr;
    cout << LCSOnlySize(aStr, bStr, cStr);
}
