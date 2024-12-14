// URL: https://www.acmicpc.net/problem/4354
// Algo: KMP

// Start:	241215 08 12
// Read:	0 2
// Think:	0 14
// Code:	0 11
// Total:   0 27

// P4 1305 광고와 아주 비슷하다. 예시: abcab, abcabc, abcabcabc
// 문자열 끝에는 패턴의 앞 부분이 나타난다.
// kmp로 구한 fail[n-1] 값이 문자열 끝에 달린 패턴의 접두사 길이를 의미하며
// 전체에서 패턴의 접두사만큼이 중복으로 나타난다는 것이므로 n - fail[n-1]이 패턴의 최소 길이가 된다.

// 위 예시들에서는 abc가 패턴이다.
// 전체 길이가 패턴 길이로 나누어 떨어지지 않으면 패턴의 반복이 아니다.

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

    string str;
    while (true)
    {
        cin >> str;
        if (str == ".") break;

        const int n = str.size();
        const auto fail = Failure(str);

        const int pattern = n - fail[n - 1];
        if (n % pattern) cout << 1 << '\n';
        else cout << n / pattern << '\n';
    }
}
