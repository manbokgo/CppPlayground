// URL: https://www.acmicpc.net/problem/2357
// Algo: 세그먼트 트리

// Start:	241122 09 24
// Read:	0 1
// Think:	0 1
// Code:	0 7
// Total:	0 9

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) x.begin(), x.end()
#define pb push_back

constexpr int INF = 0x3f3f3f3f;

template <typename T, typename F = plus<T>>
class SegTree
{
    int n;
    T defVal;

    vector<T> seg;
    F func;

public:
    explicit SegTree(int n, T defVal = T{})
        : n(n),
          defVal(defVal)
    {
        seg.resize(2 * n, defVal);
    }

    void Update(int i, T val) // O(log n)
    {
        --i;
        i += n;
        seg[i] = val;
        while (i > 1)
        {
            i /= 2;
            seg[i] = func(seg[i * 2], seg[i * 2 + 1]);
        }
    }

    T Query(int l, int r) // O(log n)
    {
        --l;
        --r;
        T ret = defVal;
        for (l += n, r += n + 1; l < r; l /= 2, r /= 2)
        {
            if (l & 1) ret = func(ret, seg[l++]);
            if (r & 1) ret = func(ret, seg[--r]);
        }
        return ret;
    }
};

struct MinInt
{
    int operator()(int a, int b) { return min(a, b); }
};

struct MaxInt
{
    int operator()(int a, int b) { return max(a, b); }
};

int main()
{
    fastio;

    int n, m;
    cin >> n >> m;

    SegTree<int, MinInt> minSeg(n, INF);
    SegTree<int, MaxInt> maxSeg(n, -1);
    for (int i = 1; i <= n; ++i)
    {
        int num;
        cin >> num;
        minSeg.Update(i, num);
        maxSeg.Update(i, num);
    }

    for (int i = 0; i < m; ++i)
    {
        int a, b;
        cin >> a >> b;
        cout << minSeg.Query(a, b) << ' ' << maxSeg.Query(a, b) << '\n';
    }
}
