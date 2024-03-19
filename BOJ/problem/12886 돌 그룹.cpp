// URL: https://www.acmicpc.net/problem/12886
// Algo: DFS or BFS

// Start:	240320 04 28
// Read:	0 0
// Think:	0 18
// Code:	0 20
// Total:	0 38

#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define Y first
#define X second
#define all(x) x.begin(), x.end()
#define SortVec(x) sort(all(x))
#define CompressVec(x) x.erase(unique(all(x)), x.end())
#define ExistInVec(x, value) find(all(x), value) != x.end()

using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using tiii = tuple<int, int, int>;
using tlll = tuple<ll, ll, ll>;

constexpr int INF = 0x3f3f3f3f;
int sum, target;

bool visited[501][1001];

bool DFS(int a, int b, int c)
{
    if (a == target && b == target) return true;

    if (a > b) swap(a, b);
    if (a > c) swap(a, c);
    if (b > c) swap(b, c);

    if (visited[a][b]) return false;
    visited[a][b] = true;

    bool ret = false;
    if (b != target && b - a > 0) // a b
    {
        ret |= DFS(2 * a, b - a, c);
    }
    if (!ret && c != target && c - a > 0) // a c
    {
        ret |= DFS(2 * a, b, c - a);
    }

    return ret;
}


/*
bool visited[1501][1501];
void BFS(int A, int B)
{
    queue<pii> q;
    visited[A][B] = true;
    q.push({A, B});

    while (!q.empty())
    {
        auto [a, b] = q.front();
        q.pop();

        int tmp[3] = {a, b, sum - a - b};
        for (int i = 0; i < 3; ++i)
        {
            for (int j = 0; j < 3; ++j)
            {
                if (tmp[i] < tmp[j])
                {
                    int na = 2 * tmp[i];
                    int nb = tmp[j] - tmp[i];
                    if (visited[na][nb]) continue;
                    visited[na][nb] = true;
                    q.push({na, nb});

                    if (na == target && nb == target) return;
                }
            }
        }
    }
}
*/


int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int a, b, c;
    cin >> a >> b >> c;

    sum = a + b + c;
    if (sum % 3 != 0)
    {
        cout << 0;
        return 0;
    }

    target = sum / 3;

    cout << DFS(a, b, c);

    // BFS(a, b);
    // cout << visited[target][target];
}
