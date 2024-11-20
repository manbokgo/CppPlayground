// URL: https://www.acmicpc.net/problem/1305
// Algo: KMP

// Start:	241121 07 41
// Read:	0 1
// Think:	0 11
// Code:	0 2
// Total:	0 14

// 좀 생각해보면 문자열의 끝부분은 광고의 접두사다.
// kmp로 구한 fail[n-1] 값이 광고의 접두사 길이를 의미하며, 전체에서 광고의 접두사만큼이
// 중복으로 나타난다는 것이므로 n - fail[n-1]이 광고의 최소 길이가 된다.

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) x.begin(), x.end()
#define pb push_back

vector<int> Failure(const string& s)
{
    vector<int> f(s.size());

    int j = 0;
    for (int i = 1; i < s.size(); i++)
    {
        while (j > 0 && s[i] != s[j])
            j = f[j - 1];
        if (s[i] == s[j])
            f[i] = ++j;
    }
    return f;
}

int main()
{
    fastio;

    int n;
    cin >> n;

    string str;
    cin >> str;

    const auto fail = Failure(str);
    cout << n - fail[n-1];
}
