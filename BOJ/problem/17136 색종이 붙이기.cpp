// URL: https://www.acmicpc.net/problem/17136
// Algo: 백트래킹

// Start:	240228 17 42
// Read:	0 0
// Think:	0 12
// Code:	0 31 실패 (그리디 풀이)
// Code:	0 40 백트래킹
// Total:	1 23

#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define X first
#define Y second
#define all(x) x.begin(), x.end()
#define sortVec(x) sort(all(x))
#define compress(x) x.erase(unique(all(x)), x.end())
#define existInVec(x, value) find(all(x), value) != x.end()

using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using tiii = tuple<int, int, int>;
using tlll = tuple<ll, ll, ll>;

constexpr int INF = 0x3f3f3f3f;
// constexpr ll  LLINF = 1e18;
// constexpr ll  MOD = 1000000007;

bool tile[10][10];
int  avail[6] = {-1, 5, 5, 5, 5, 5};
int  maxFilled = 0;
int  answer = INF;

bool Check(int y, int x, int size)
{
    if (avail[size] == 0) return false;
    if (y + size - 1 >= 10 || x + size - 1 >= 10) return false;

    for (int i = y; i < y + size; ++i)
    {
        for (int j = x; j < x + size; ++j)
        {
            if (!tile[i][j]) return false;
        }
    }

    return true;
}

void FillTile(int y, int x, int size, bool b)
{
    if (!b) --avail[size];
    else ++avail[size];

    for (int i = y; i < y + size; ++i)
    {
        for (int j = x; j < x + size; ++j)
        {
            tile[i][j] = b;
        }
    }
}

void Solve(int used, int filled, int prevY, int prevX)
{
    if (used >= answer) return;
    if (filled == maxFilled)
    {
        answer = min(answer, used);
        return;
    }

    int y = prevY;
    int x = prevX;
    if (x >= 10)
    {
        ++y;
        x = 0;
    }

    while (!tile[y][x])
    {
        ++x;
        if (x >= 10)
        {
            ++y;
            x = 0;
        }
    }

    for (int size = 5; size > 0; --size)
    {
        if (Check(y, x, size))
        {
            FillTile(y, x, size, false);
            Solve(used + 1, filled + size * size, y, x + size);
            FillTile(y, x, size, true);
        }
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    for (int i = 0; i < 10; ++i)
    {
        for (int j = 0; j < 10; ++j)
        {
            cin >> tile[i][j];
            if (tile[i][j]) ++maxFilled;
        }
    }

    Solve(0, 0, 0, 0);

    if (answer == INF) cout << -1;
    else cout << answer;
}
