// URL: https://www.acmicpc.net/problem/9252
// Algo: DP (LCS)

// Start:	240312 18 36
// Read:	0 0
// Think:	0 1
// Code:	0 9
// Total:	0 10

// https://velog.io/@emplam27/%EC%95%8C%EA%B3%A0%EB%A6%AC%EC%A6%98-%EA%B7%B8%EB%A6%BC%EC%9C%BC%EB%A1%9C-%EC%95%8C%EC%95%84%EB%B3%B4%EB%8A%94-LCS-%EC%95%8C%EA%B3%A0%EB%A6%AC%EC%A6%98-Longest-Common-Substring%EC%99%80-Longest-Common-Subsequence

#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define Y first
#define X second
#define all(x) x.begin(), x.end()
#define SortVec(x) sort(all(x))
#define CompressVec(x) x.erase(unique(all(x)), x.end())
#define ExistInVec(x, value) find(all(x), value) != x.end()

using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using tiii = tuple<int, int, int>;
using tlll = tuple<ll, ll, ll>;

constexpr int INF = 0x3f3f3f3f;

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
}
