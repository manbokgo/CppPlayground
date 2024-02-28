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

// int dy[4] = {0, 1, 0, -1};
// int dx[4] = {1, 0, -1, 0}; // 동남서북
bool OOB(int y, int x) { return y < 0 || y >= 10 || x < 0 || x >= 10; }

bool tile[10][10];
int  avail[6] = {-1, 5, 5, 5, 5, 5};
int  maxFilled = 0;
int  answer = INF;

bool Check(int y, int x, int size)
{
    if (avail[size] == 0) return false;
    for (int i = 0; i < size; ++i)
    {
        for (int j = 0; j < size; ++j)
        {
            // 최적화 가능하긴한데 일단 넘김
            int ny = y + i;
            int nx = x + j;
            if (OOB(ny, nx)) return false;
            if (!tile[ny][nx]) return false;
        }
    }

    return true;
}

void FillTile(int y, int x, int size, bool b)
{
    if (!b) --avail[size];
    else ++avail[size];

    for (int i = 0; i < size; ++i)
    {
        for (int j = 0; j < size; ++j)
        {
            int ny = y + i;
            int nx = x + j;
            tile[ny][nx] = b;
        }
    }
}

void Solve(int used, int filled)
{
    if (used >= answer) return;
    if (filled == maxFilled)
    {
        answer = min(answer, used);
        return;
    }

    int y = -1;
    int x = -1;
    for (int i = 0; i < 10; ++i)
    {
        for (int j = 0; j < 10; ++j)
        {
            if (tile[i][j])
            {
                y = i;
                x = j;
                break;
            }
        }
        if (y != -1) break;
    }

    for (int size = 5; size > 0; --size)
    {
        if (Check(y, x, size))
        {
            FillTile(y, x, size, false);
            Solve(used + 1, filled + size * size);
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

    Solve(0, 0);

    if (answer == INF) cout << -1;
    else cout << answer;
}
