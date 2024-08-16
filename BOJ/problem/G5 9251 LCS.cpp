// URL: https://www.acmicpc.net/problem/9251
// Algo: DP (LCS 기본)

// Start:	240816 09 05
// Read:	0 2
// Think:	0 2
// Code:	0 8
// Total:	0 12

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) x.begin(), x.end()
#define pb push_back

int LCS[1001][1001];

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string aStr, bStr;
    cin >> aStr >> bStr;

    for (int i = 0; i <= aStr.size(); ++i)
    {
        for (int j = 0; j <= bStr.size(); ++j)
        {
            if (i == 0 || j == 0)
                LCS[i][j] = 0;
            else if (aStr[i - 1] == bStr[j - 1])
                LCS[i][j] = LCS[i - 1][j - 1] + 1;
            else
                LCS[i][j] = max(LCS[i - 1][j], LCS[i][j - 1]);
        }
    }

    cout << LCS[aStr.size()][bStr.size()];
    /*
    if (LCS[aStr.size()][bStr.size()] > 0)
    {
        cout << "\n";

        string answer;

        for (int i = aStr.length(), j = bStr.length();;)
        {
            int cur = LCS[i][j];
            if (cur == 0) break;

            if (cur == LCS[i - 1][j]) --i;
            else if (cur == LCS[i][j - 1]) --j;
            else
            {
                answer.pb(aStr[i - 1]);
                --i;
                --j;
            }
        }

        reverse(all(answer));
        cout << answer;
    }
    */
}
