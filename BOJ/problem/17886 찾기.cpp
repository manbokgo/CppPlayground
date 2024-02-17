// URL: https://www.acmicpc.net/problem/1786
// Algo: KMP 기본 (S에서 P 찾기)

// Start:	240218 01 00
// Read:	0 1
// Think:	0 0
// Code:	0 20
// Total:	0 21

#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define X first
#define Y second
#define all(x) x.begin(), x.end()
#define sortvec(x) sort(all(x))
#define compress(x) x.erase(unique(all(x)), x.end())
#define findvec(x, value) find(all(x), value) != x.end()

using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;

constexpr ll  MOD = 1000000007;
constexpr int INF = 0x3f3f3f3f;
constexpr ll  LLINF = 1e18;

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
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string S, P;
    getline(cin, S);
    getline(cin, P);

    vector<int> fail = Failure(P);

    vector<int> results;
    int         j = 0;
    for (int i = 0; i < S.size(); i++) // 실수: i=0에서 시작. fail 함수 무지성으로 복사 금지.
    {
        while (j > 0 && S[i] != P[j])
            j = fail[j - 1];
        if (S[i] == P[j])
        {
            if (j == P.size() - 1)
            {
                results.pb(i - P.size() + 2);
                // 실수: 다음 i에 들어갈 j를 넣는 것이니 fail[j-1]이 아니라 fail[j] 여야함
                // ex) ABCABD 에서 ABCAB 를 완전히 매칭시킨 상황에서
                // S의 다음 매칭인 D에는 P의 접두사 AB가 유효함
                // P의 C를 가리키도록 j에는 fail[4] = 3 넣어야함
                j = fail[j];
            }
            else
            {
                ++j;
            }
        }
    }

    cout << results.size() << "\n";
    for (int result : results)
    {
        cout << result << " ";
    }
}
