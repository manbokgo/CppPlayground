// URL: https://www.acmicpc.net/problem/1786
// Algo: KMP 기본 (S에서 P 찾기)

// Start:	240218 01 00
// Read:	0 1
// Think:	0 0
// Code:	0 20
// Total:	0 21

// https://blog.encrypted.gg/1040
// KMP fail[x] : x 인덱스까지의 문자열(앞에서부터 x+1개의 문자열)에서 접두사가 끝난 후의 인덱스(접두사의 문자 개수)

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

    string S, P;
    getline(cin, S);
    getline(cin, P);

    vector<int> fail = Failure(P);

    vector<int> results;
    int j = 0;
    for (int i = 0; i < S.size(); i++) // 실수: i=0에서 시작. fail 함수 무지성으로 복사 금지.
    {
        while (j > 0 && S[i] != P[j])
            j = fail[j - 1];

        if (S[i] == P[j])
        {
            ++j;
            if (j == P.size())
            {
                results.pb(i - P.size() + 2);
                // ex) ABCABD 에서 ABCAB 를 완전히 매칭시킨 상황에서
                // S의 다음 매칭인 D에는 P의 접두사 AB가 유효함
                // P의 C를 가리키도록 j에는 fail[4] = 2 넣어야함
                j = fail[j - 1];
            }
        }
    }

    cout << results.size() << "\n";
    for (int result : results)
    {
        cout << result << " ";
    }
}
