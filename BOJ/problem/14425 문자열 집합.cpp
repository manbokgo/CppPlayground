// URL: https://www.acmicpc.net/problem/14425
// Algo: 트라이 기본.
//
// 사실 그냥 unordered_set으로 풀 수 있는 문제이긴 하나
// 메모리 1536MB 제한으로 트라이로 한번 풀어보라는 의도의 문제임

// Start:	240215 20 46
// Read:	20 46
// Think:	20 46
// Code:	20 54
// Total:	0 8

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

const int ROOT = 1;
int       unused = 2;
const int MX = 10000 * 500 + 5;
bool      chk[MX];
int       nxt[MX][26];


int C2I(char c)
{
    return c - 'a';
}

void Insert(const string& s)
{
    int cur = ROOT;
    for (char c : s)
    {
        if (nxt[cur][C2I(c)] == -1)
            nxt[cur][C2I(c)] = unused++;
        cur = nxt[cur][C2I(c)];
    }
    chk[cur] = true;
}

bool Find(const string& s)
{
    int cur = ROOT;
    for (char c : s)
    {
        if (nxt[cur][C2I(c)] == -1)
            return false;
        cur = nxt[cur][C2I(c)];
    }
    return chk[cur];
}

void Erase(const string& s)
{
    int cur = ROOT;
    for (char c : s)
    {
        if (nxt[cur][C2I(c)] == -1)
            return;
        cur = nxt[cur][C2I(c)];
    }
    chk[cur] = false;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    for (auto& i : nxt)
    {
        fill_n(i, 26, -1);
    }

    int n, m;
    string text;
    int ans = 0;

    cin >> n >> m;

    while (n--)
    {
        cin >> text;
        Insert(text);
    }

    while (m--)
    {
        cin >> text;
        if (Find(text)) ++ans;
    }

    cout << ans;
}
