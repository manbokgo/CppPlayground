// URL: https://www.acmicpc.net/problem/17136
// Algo: 

// Start:	240228 17 42
// Read:	0 0
// Think:	0 12
// Code:	0 31
// Total:	

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

int Possible(int y, int x)
{
    if (OOB(y, x)) return 0;
    if (!tile[y][x]) return 0;

    int maxSize = 0;
    for (int range = 1; range <= 5; ++range)
    {
        if (avail[range] == 0) continue;
        for (int i = 0; i < range; ++i)
        {
            for (int j = 0; j < range; ++j)
            {
                // 최적화 가능하긴한데 일단 넘김
                int ny = y + i;
                int nx = x + j;
                if (OOB(ny, nx)) goto Exit;
                if (!tile[ny][nx]) goto Exit;
            }
        }

        maxSize = range;
    }

Exit:
    return maxSize;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int count = 0;
    int answer = 0;

    for (int i = 0; i < 10; ++i)
    {
        for (int j = 0; j < 10; ++j)
        {
            cin >> tile[i][j];
            if (tile[i][j]) ++count;
        }
    }

    if (count == 0)
    {
        cout << 0;
        return 0;
    }

    priority_queue<tiii> pq;

    for (int i = 0; i < 10; ++i)
    {
        for (int j = 0; j < 10; ++j)
        {
            int size = Possible(i, j);
            if (size == 0) continue;
            pq.push({size, i, j});
        }
    }

    while (!pq.empty())
    {
        if (count == 0) break;

        auto [size, y, x] = pq.top();
        pq.pop();

        if (int checkSize = Possible(y, x); checkSize != size)
        {
            if (checkSize > 0)
                pq.push({checkSize, y, x});
            continue;
        }

        for (int i = 0; i < size; ++i)
        {
            for (int j = 0; j < size; ++j)
            {
                int ny = y + i;
                int nx = x + j;
                tile[ny][nx] = false;
            }
        }

        --avail[size];
        count -= (size) * (size);
        ++answer;
    }

    if (count > 0) cout << -1;
    else cout << answer;
}
