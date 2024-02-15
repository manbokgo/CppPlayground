// URL: https://www.acmicpc.net/problem/5052
// Algo: 트라이

// Start:	240216 01 17
// Read:	0 0
// Think:	0 1
// Code:	0 34
// Total:	0 35

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

constexpr int ROOT = 1;
int           unused = 2;
constexpr int MX = 10'000 * 10 + 5;
bool          chk[MX];
int           nxt[MX][10];

int C2I(char c)
{
    return c - '0';
}


bool Insert(const string& s)
{
    int cur = ROOT;
    for (int i = 0; i < s.size(); ++i)
    {
        int idx = C2I(s[i]);
        if (nxt[cur][idx] == -1)
        {
            nxt[cur][idx] = unused++;
        }
        else
        {
            if (i == s.size() - 1) return false; // 실수: 111, 11 경우처럼 마지막 번호 입력에도 이미 입력되어있다면 뻑남
            if (chk[nxt[cur][idx]]) return false;
        }
        cur = nxt[cur][idx];
    }

    chk[cur] = true;
    return true;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int    t, n;
    string text;

    cin >> t;
    while (t--)
    {
        // 실수: 테스트 케이스마다 unused, chk, nxt 초기화
        unused = 2;
        memset(chk, false, sizeof(chk));
        memset(nxt, -1, sizeof(nxt));

        cin >> n;
        while (n--)
        {
            cin >> text;
            if (!Insert(text))
            {
                cout << "NO\n";
                while (n--) cin >> text; // 실수: 남은 전화번호들 지워줘야함. 그냥 처음에 cin으로 string 배열에 몽땅 다 담고 진행하는게 더 간편한가?
                goto Fail;
            }
        }
        cout << "YES\n";
    Fail:;
    }
}
