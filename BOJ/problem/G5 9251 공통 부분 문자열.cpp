// URL: https://www.acmicpc.net/problem/5582
// Algo: DP (최장 공통 문자열 LCStr 기본)

// Start:	241124 09 37
// Read:	0 1
// Think:	0 1
// Code:	0 5
// Total:	0 7

// Longest Common Substring
// https://velog.io/@emplam27/%EC%95%8C%EA%B3%A0%EB%A6%AC%EC%A6%98-%EA%B7%B8%EB%A6%BC%EC%9C%BC%EB%A1%9C-%EC%95%8C%EC%95%84%EB%B3%B4%EB%8A%94-LCS-%EC%95%8C%EA%B3%A0%EB%A6%AC%EC%A6%98-Longest-Common-Substring%EC%99%80-Longest-Common-Subsequence

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) x.begin(), x.end()
#define pb push_back

int LCStr[4001][4001];

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string aStr, bStr;
    cin >> aStr >> bStr;

    int ans = 0;
    for (int i = 1; i <= aStr.size(); ++i)
    {
        for (int j = 1; j <= bStr.size(); ++j)
        {
            if (aStr[i - 1] == bStr[j - 1])
            {
                LCStr[i][j] = LCStr[i - 1][j - 1] + 1;
                ans = max(ans, LCStr[i][j]);
            }
            else
            {
                LCStr[i][j] = 0; // LCS(부분수열)과 이 부분만 다르다
            }
        }
    }
    cout << ans;
}
