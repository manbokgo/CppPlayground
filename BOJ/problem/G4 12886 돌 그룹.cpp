// URL: https://www.acmicpc.net/problem/12886
// Algo: DFS or BFS

// Start:	240320 04 28
// Read:	0 0
// Think:	0 18
// Code:	0 20
// Total:	0 38
// https://manbokgo.notion.site/G4-12886-C-gcc-de061675848b47b793bb7cea79f35c2f?pvs=74

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) x.begin(), x.end()
#define pb push_back

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

    /*
    bool ret = false;
    if (b != target && b - a > 0) // a b
    {
        ret = DFS(2 * a, b - a, c);
    }
    if (!ret && c != target) // a c
    {
        ret = DFS(2 * a, b, c - a);
    }
    return ret;
    */

    // 깔끔하지만 약간 비효율적
    return DFS(a + a, b - a, c) || DFS(a + a, b, c - a);
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
