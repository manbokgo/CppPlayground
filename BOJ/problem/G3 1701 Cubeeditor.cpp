// URL: https://www.acmicpc.net/problem/1701
// Algo: KMP 기본

// Start:	240218 00 04
// Read:	0 1
// Think:	0 1
// Code:	0 5     Fail
// Think:   0 3     ccabccab처럼 처음부터 시작하는 접두사가 아닌 경우도 고려해야함
// Code:	0 10    string erase 잘못 써서 헤맴
// Total:	0 20

// https://blog.encrypted.gg/1040
// i: 위 인덱스. 비교할 대상 문자.
// j: 아래 인덱스. 불일치하면 fail로 최대한 일치 구간을 유지하면서 앞쪽으로 옮겨감.
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

    string text;
    cin >> text;

    int result = 0;;
    do
    {
        vector<int> fail = Failure(text);
        result = max(result, *max_element(all(fail)));
        text.erase(0, 1);
    } while (!text.empty());

    cout << result;
}
