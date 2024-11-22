// URL: https://www.acmicpc.net/problem/2042
// Algo: 펜윅 트리 기본 (BIT)

// Start:	241122 07 48
// Read:	0 1
// Think:	0 1
// Code:	0 24
// Total:	0 26

// https://greeksharifa.github.io/algorithm%20&%20data%20structure/2018/07/09/algorithm-fenwick-tree/
// https://yabmoons.tistory.com/438

// 세그먼트 트리에서 '누적' 연산에 특화되어, 시간 복잡도는 O(Q log N)으로 동일하지만
// 더 적은 시간과 메모리를 사용하는 자료 구조.
// 2차원 배열에서의 구간 합을 구할 때 2차원 펜윅 트리를 사용하기도 한다.

// 한계: '누적'하는 것이기 때문에 불가능한 경우가 있다.
// 누적 합처럼 특정 구간의 쿼리 결과를 Sum(b) - Sum(a-1)로 구해오는 식이기 때문에
// 1~x까지의 합/곱/최댓값/GCD이나, a~b까지의 합/곱은 가능하지만
// a~b까지의 최댓값/GCD는 불가능하다. 이럴 때는 세그먼트 트리를 사용해야 한다.

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) x.begin(), x.end()
#define pb push_back

using ll = long long;

// 1-indexed. 메모리 2n.
template <typename T, typename F = plus<T>>
class FwTree
{
    int n;
    T defVal;

    vector<T> arr;
    vector<T> tree;
    F func;

    T Sum(int idx)
    {
        T ret = defVal;
        while (idx > 0)
        {
            ret = func(ret, tree[idx]);
            idx -= (idx & -idx);
        }
        return ret;
    }

public:
    FwTree(int n, T defVal = T{})
        : n(n),
          defVal(defVal)
    {
        arr.resize(n + 1);
        tree.resize(n + 1, defVal);
    }

    void Update(int idx, T val)
    {
        T diff = val - arr[idx];
        arr[idx] = val;

        while (idx <= n)
        {
            tree[idx] = func(tree[idx], diff);
            idx += (idx & -idx);
        }
    }

    T Sum(int a, int b)
    {
        return Sum(b) - Sum(a - 1);
    }
};

int main()
{
    fastio;

    int n, m, k;
    cin >> n >> m >> k;

    FwTree<ll> fwTree(n);
    for (int i = 1; i <= n; ++i)
    {
        ll num;
        cin >> num;
        fwTree.Update(i, num);
    }

    for (int i = 0; i < m + k; ++i)
    {
        int a, b;
        ll c;
        cin >> a >> b >> c;

        if (a == 1) fwTree.Update(b, c);
        else cout << fwTree.Sum(b, c) << '\n';
    }
}
