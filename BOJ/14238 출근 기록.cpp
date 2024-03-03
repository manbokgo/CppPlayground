// URL: https://www.acmicpc.net/problem/14238
// Algo: DP, 백트래킹 (DFS)

// Start:	240304 00 04
// Read:	0 0
// Think:	0 2
// Code:	0 8 백트래킹 시간초과
// Code:	0 30 백트래킹 최적화로 삽질하다가, 시간초과는 메모리랑 등가교환하는 DP가 답임을 깨닫고 품.
// Total:	0 40

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

const ll  MOD = 1000000007;
const int INF = 0x3f3f3f3f;
const ll  LLINF = 1e18;


int  len;
char answer[51];
int  cnt[3];

// 전전날C?, 전날B?, 남은C, 남은B, 남은A
bool dp[2][2][51][51][51];

void Backtracking(int depth, int b, int c)
{
    if (depth == len)
    {
        cout << answer;
        exit(0);
    }

    if (dp[c ? 1 : 0][b ? 1 : 0][cnt[2]][cnt[1]][cnt[0]])
    {
        return;
    }


    if (c == 0 && cnt[2])
    {
        --cnt[2];
        answer[depth] = 'C';

        Backtracking(depth + 1, b ? b - 1 : 0, 2);

        ++cnt[2];
        answer[depth] = 0;
    }

    if (b == 0 && cnt[1])
    {
        --cnt[1];
        answer[depth] = 'B';

        Backtracking(depth + 1, 1, c ? c - 1 : 0);

        ++cnt[1];
        answer[depth] = 0;
    }

    if (cnt[0])
    {
        --cnt[0];
        answer[depth] = 'A';

        Backtracking(depth + 1, b ? b - 1 : 0, c ? c - 1 : 0);

        ++cnt[0];
        answer[depth] = 0;
    }

    dp[c ? 1 : 0][b ? 1 : 0][cnt[2]][cnt[1]][cnt[0]] = true;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string str;
    cin >> str;
    len = str.length();
    for (char c : str)
    {
        ++cnt[c - 'A'];
    }

    
    if (cnt[2] > len / 3 + 1)
    {
        cout << -1;
        return 0;
    }

    if (cnt[1] > len / 2 + 1)
    {
        cout << -1;
        return 0;
    }

    Backtracking(0, 0, 0);
    cout << -1;
}
