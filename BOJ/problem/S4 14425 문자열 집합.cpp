// URL: https://www.acmicpc.net/problem/14425
// Algo: 트라이 기본

// Start:	240215 20 46
// Read:	0 0
// Think:	0 0
// Code:	0 8
// Total:	0 8

// 사실 그냥 unordered_set으로 풀 수 있는 문제이긴 하나
// 메모리 1536MB 제한을 보면 트라이로 한번 풀어보라는 의도의 문제임

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) x.begin(), x.end()
#define pb push_back

constexpr int ROOT = 1;
int unused = 2;

constexpr int MX = 10000 * 500 + 5;
bool chk[MX];
int nxt[MX][26];

inline int C2I(char c) { return c - 'a'; }

bool Insert(const string& s)
{
    int cur = ROOT;
    for (const char c : s)
    {
        if (nxt[cur][C2I(c)] == -1) nxt[cur][C2I(c)] = unused++;
        cur = nxt[cur][C2I(c)];
    }

    chk[cur] = true;
    return true;
}

bool Find(const string& s)
{
    int cur = ROOT;
    for (const char c : s)
    {
        if (nxt[cur][C2I(c)] == -1) return false;
        cur = nxt[cur][C2I(c)];
    }
    return chk[cur];
}

bool Erase(const string& s)
{
    int cur = ROOT;
    for (const char c : s)
    {
        if (nxt[cur][C2I(c)] == -1) return false;
        cur = nxt[cur][C2I(c)];
    }
    if (!chk[cur]) return false;

    chk[cur] = false;
    return true;
}

int main()
{
    fastio;
    memset(nxt, -1, sizeof(nxt));

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
