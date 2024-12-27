// URL: https://www.acmicpc.net/problem/2195
// Algo: 그리디

// Start:	241228 00 34
// Read:	0 2
// Think:	0 3
// Code:	0 6
// Total:	0 11

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) x.begin(), x.end()
#define pb push_back

int main()
{
    fastio;

    string s, p;
    cin >> s >> p;

    int answer = 0;
    for (int i = 0; i < p.length();)
    {
        int mxLen = 0;
        for (int j = 0; j < s.length(); ++j)
        {
            int tmp = 0;
            while (j + tmp < s.length() &&
                i + tmp < p.length() &&
                s[j + tmp] == p[i + tmp])
                ++tmp;
            mxLen = max(mxLen, tmp);
        }
        i += mxLen;
        ++answer;
    }
    cout << answer;
}
