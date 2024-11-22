// URL: https://www.acmicpc.net/problem/11505
// Algo: 세그먼트 트리 기본 (탑다운)

// Start:	241119 05 02
// Read:	0 1
// Think:	0 5
// Code:	0 41
// Total:	0 48

// 완전히 재귀로 구현하는 세그먼트 트리.
// https://book.acmicpc.net/ds/segment-tree

// https://www.acmicpc.net/source/86608389
// arr 배열과 Init 함수를 따로 둘 필요없이, 바텀 업처럼 offset을 두어
// seg[offset]~seg[2offset-1]에 arr 값을 저장하여, 초기화와 Update를 O(N)만에 할 수도 있다.

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) x.begin(), x.end()
#define pb push_back

using ll = long long;
constexpr ll MOD = 1000000007;

// 1-indexed 탑다운. 메모리 4n
template <typename T, typename F = plus<T>>
class SegTree
{
    int n;
    T defVal;

    vector<T> arr;
    vector<T> seg;
    F func;

    T Init(int idx, int st, int en)
    {
        if (st == en) return seg[idx] = arr[st];

        const int mid = (st + en) / 2;
        return seg[idx] = func(Init(2 * idx, st, mid), Init(2 * idx + 1, mid + 1, en));
    }

    T Update(int idx, int st, int en, int i, int val)
    {
        if (i > en || i < st) return seg[idx];
        if (st == en) return seg[idx] = val;

        const int mid = (st + en) / 2;
        return seg[idx] = func(Update(2 * idx, st, mid, i, val), Update(2 * idx + 1, mid + 1, en, i, val));
    }

    T Query(int idx, int st, int en, int l, int r)
    {
        if (l > en || r < st) return defVal;
        if (l <= st && en <= r) return seg[idx];

        const int mid = (st + en) / 2;
        return func(Query(2 * idx, st, mid, l, r), Query(2 * idx + 1, mid + 1, en, l, r));
    }

public:
    explicit SegTree(int n, T defVal = T{})
        : n(n),
          defVal(defVal)
    {
        arr.resize(n);

        const int h = (int)ceil(log2(n));
        const int treeSz = (1 << (h + 1));
        seg.resize(treeSz, defVal);
    }

    explicit SegTree(const vector<T>& arr, T defVal = T{})
        : n(arr.size()),
          defVal(defVal),
          arr(arr)
    {
        const int h = (int)ceil(log2(n));
        const int treeSz = (1 << (h + 1));
        seg.resize(treeSz, defVal);

        Init(1, 0, n - 1);
    }

    void Update(int i, T val) // O(log n)
    {
        --i;
        arr[i] = val;
        Update(1, 0, n - 1, i, val);
    }

    T Query(int l, int r) // O(log n)
    {
        --l;
        --r;
        return Query(1, 0, n - 1, l, r);
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

        if (a == 1) seg.Update(b, c);
        else cout << seg.Query(b, c) << '\n';
    }
}
