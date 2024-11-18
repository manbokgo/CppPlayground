// URL: https://www.acmicpc.net/problem/2042
// Algo: 세그먼트 트리 기본 (바텀업)

// Start:	241118 05 38
// Read:	0 1
// Think:	1 10
// Code:	0 24
// Total:	1 35

// 세그먼트 트리 공부.
// TODO: 펜윅 트리(BIT)

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) x.begin(), x.end()
#define pb push_back

using ll = long long;

// 0-indexed 바텀업. 메모리 2n
// https://infossm.github.io/blog/2019/11/15/2D-segment-tree/

template <typename T, typename F = plus<T>>
class SegTree
{
    int n;
    T defVal;

    vector<T> seg;
    F func;

public:
    explicit SegTree(int n, T defVal = T{})
        : n(n), defVal(defVal)
    {
        seg.resize(2 * n, defVal);
    }

    // arr 배열을 따로 만드는대신, seg를 외부에 노출시킨 후
    // 직접 seg[n]~seg[2n-1]에 값을 넣어주는게 더 효율적이다.
    explicit SegTree(const vector<T>& arr, T defVal = T{})
        : n(arr.size()), defVal(defVal)
    {
        seg.resize(2 * n, defVal);
        for (int i = 0; i < n; ++i)
            seg[i + n] = arr[i];

        for (int i = n - 1; i > 0; i--) // O(n)
            seg[i] = func(seg[i * 2], seg[i * 2 + 1]);
    }

    void Update(int i, T val) // O(log n)
    {
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
        T ret = defVal;
        for (l += n, r += n + 1; l < r; l /= 2, r /= 2)
        {
            if (l & 1) ret = func(ret, seg[l++]);
            if (r & 1) ret = func(ret, seg[--r]);
        }
        return ret;
    }
};

int main()
{
    fastio;

    int n, m, k;
    cin >> n >> m >> k;

    SegTree<ll> seg(n);
    for (int i = 0; i < n; ++i)
    {
        ll num;
        cin >> num;
        seg.Update(i, num);
    }

    for (int i = 0; i < m + k; ++i)
    {
        int a, b;
        ll c;
        cin >> a >> b >> c;

        if (a == 1) seg.Update(b - 1, c);
        else cout << seg.Query(b - 1, c - 1) << '\n';
    }
}
