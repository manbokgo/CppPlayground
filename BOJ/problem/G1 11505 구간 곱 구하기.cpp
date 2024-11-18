// URL: https://www.acmicpc.net/problem/11505
// Algo: 세그먼트 트리 기본 (탑다운)

// Start:	241119 05 02
// Read:	0 1
// Think:	0 5
// Code:	0 41
// Total:	0 48

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) x.begin(), x.end()
#define pb push_back

using ll = long long;
constexpr ll MOD = 1000000007;

// 0-indexed 탑다운. 메모리 4n
// https://book.acmicpc.net/ds/segment-tree

template <typename T, typename F = plus<T>>
class SegTree
{
    int n;
    int offset;
    T defVal;

    vector<T> seg;
    F func;

    T Query(int l, int r, int idx, int st, int en)
    {
        if (l > en || r < st) return defVal;
        if (l <= st && en <= r) return seg[idx];
        const int mid = (st + en) / 2;
        return func(Query(l, r, 2 * idx, st, mid), Query(l, r, 2 * idx + 1, mid + 1, en));
    }

public:
    explicit SegTree(int n, T defVal = T{})
        : n(n), defVal(defVal)
    {
        const int h = (int)ceil(log2(n));
        const int treeSz = (1 << (h + 1));

        offset = (1 << h);
        seg.resize(treeSz, defVal);
    }

    explicit SegTree(const vector<T>& arr, T defVal = T{})
        : n(arr.size()), defVal(defVal)
    {
        const int h = (int)ceil(log2(n));
        const int treeSz = (1 << (h + 1));

        offset = (1 << h);
        seg.resize(treeSz, defVal);

        for (int i = 0; i < n; ++i)
            seg[i + offset] = arr[i];

        for (int i = offset - 1; i > 0; i--) // O(n)
            seg[i] = func(seg[i * 2], seg[i * 2 + 1]);
    }

    void Update(int i, T val) // O(log n)
    {
        i += offset;
        seg[i] = val;
        while (i > 1)
        {
            i /= 2;
            seg[i] = func(seg[i * 2], seg[i * 2 + 1]);
        }
    }

    T Query(int l, int r) // O(log n)
    {
        return Query(l, r, 1, 0, offset - 1);
    }
};

struct mul
{
    constexpr int operator()(const int l, const int r) const
    {
        return 1LL * l * r % MOD;
    }
};

int main()
{
    fastio;
    
    int n, m, k;
    cin >> n >> m >> k;

    vector<int> arr(n);
    for (auto& num : arr) cin >> num;

    SegTree<int, mul> seg(arr, 1);

    for (int i = 0; i < m + k; ++i)
    {
        int a, b, c;
        cin >> a >> b >> c;

        if (a == 1) seg.Update(b - 1, c);
        else cout << seg.Query(b - 1, c - 1) << '\n';
    }
}
