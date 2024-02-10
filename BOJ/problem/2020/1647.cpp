// Union-Find 크루스칼 최소 스패닝 트리
#include <bits/stdc++.h>
using namespace std;

int uf[100000];
int find(int a)
{
    if (uf[a] < 0)
        return a;
    return uf[a] = find(uf[a]);
}

bool merge(int a, int b)
{
    a = find(a);
    b = find(b);
    if (a == b)
        return false;
    if (a < b)
        uf[b] = a;
    else
        uf[a] = b;
    return true;
}

struct Edge
{
    int u, v, w;
    bool operator<(const Edge &a) const { return w < a.w; }
};

Edge edge[1000000];
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    for (int i = 0; i < m; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        edge[i] = {u, v, w};
    }

    sort(edge, edge + m);

    int result = 0;
    int cnt = 0;
    fill(uf, uf + sizeof(uf) / sizeof(int), -1);
    for (auto &&cur : edge)
    {
        if (merge(cur.u, cur.v))
        {
            result += cur.w;
            if (++cnt == n - 2)
                break;
        }
    }
    cout << result;
}