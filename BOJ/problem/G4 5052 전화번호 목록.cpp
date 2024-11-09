// URL: https://www.acmicpc.net/problem/5052
// Algo: 트라이

// Start:	240216 01 17
// Read:	0 0
// Think:	0 1
// Code:	0 34
// Total:	0 35

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) x.begin(), x.end()
#define pb push_back

constexpr int ROOT = 1;
int unused = 2;

constexpr int MX = 10'000 * 10 + 5;
bool chk[MX];
int nxt[MX][10];

inline int C2I(char c) { return c - '0'; }

bool Insert(const string& s)
{
    int cur = ROOT;
    for (int i = 0; i < s.size(); ++i)
    {
        const int idx = C2I(s[i]);
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
    fastio;

    int T, n;
    cin >> T;
    while (T--)
    {
        unused = 2;
        memset(chk, false, sizeof(chk));
        memset(nxt, -1, sizeof(nxt));

        cin >> n;
        vector<string> arr(n);
        for (auto& str : arr) cin >> str;

        bool success = true;
        for (const string& str : arr)
        {
            if (!Insert(str))
            {
                success = false;
                break;
            }
        }

        if (success) cout << "YES\n";
        else cout << "NO\n";
    }
}
