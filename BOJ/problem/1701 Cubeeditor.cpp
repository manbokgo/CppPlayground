// URL: https://www.acmicpc.net/problem/1701
// Algo: KMP 기본

// Start:	240218 00 04
// Read:	0 1
// Think:	0 1
// Code:	0 5     Fail
// Think:   0 3     ccabccab처럼 처음부터 시작하는 접두사가 아닌 경우도 고려해야함
// Code:	0 10    string erase 잘못 써서 헤맴
// Total:	0 20

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
