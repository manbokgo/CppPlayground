// URL: https://www.acmicpc.net/problem/1517
// Algo: 세그먼트 트리 or 분할 정복

// Start:	250128 17 27
// Read:	0 1
// Think:	0 17
// Code:	0 10
// Total:	0 28
// 오모시로이

// 버블 소트는 O(n^2)이므로 당연히 직접 버블 소트를 하면서 횟수를 알아내는 건 안 된다.

// Inversion Counting 이라는 유명한 유형의 문제로,
// i < j 이면서 A[i] > A[j]인 쌍(=Inversion)의 개수를 세는 문제다.

// 풀어서 말하면, 어떤 요소가 스왑되는 횟수는 그 요소의 오른쪽에 있는 더 작은 숫자들의 개수와 같다.
// 따라서 모든 요소에 대해, 각각 자신의 오른쪽에 더 작은 숫자가 몇 개인지를 모두 세어 합해주어야 하낟.

// 세그먼트 트리 O(nlogn)로 풀었다.
// 단순한 구간 합 세그먼트 트리로 '특정 구간에서 현재 요소보다 더 작은 숫자 개수'가 저장되어 있다.

// {값, 인덱스} 쌍으로 입력을 받고, 오름차순으로 정렬을 한 후 가장 값이 작은 숫자부터 순회한다.
// 인덱스+1 ~ N 구간을 쿼리하면 현재 요소보다 오른쪽에 존재하는, 더 작은 숫자의 개수를 알 수 있고 이를 정답에 더한다.
// 이후 인덱스 에 1을 업데이트하면 다음 요소는 현재 요소까지 포함하여 더 작은 숫자 개수를 세게 된다.

// 세그먼트 트리 자체는 단순한 구간 합이므로 펜윅 트리를 사용할 수 있다.

// https://velog.io/@statco19/1517%EB%B2%88-%EB%B2%84%EB%B8%94%EC%86%8C%ED%8A%B8-C


// 보다 비직관적인 방법으로, 세그먼트 트리(펜윅 트리)를 '특정 수 범위에서 현재 요소보다 더 오른쪽에 있던 숫자 개수'로 정의할 수 있다.
// 각 요소별로 정렬된 후의 인덱스를 찾아내고, 원래 배열에서 맨오른쪽부터 순회하여  0 ~ 정렬후인덱스-1 를 쿼리해서
// 현재 요소보다 더 오른쪽에 있고, 정렬 후 인덱스보다 더 작으니 더 작은 숫자인 개수를 셀 수 있다.
// 이후 정렬 후 인덱스에 1을 업데이트한다. 굳이?

// https://nicotina04.tistory.com/113


// 분할 정복, 병합 정렬(머지 소트)의 과정을 이용하여 Inversion을 셀 수도 있다.
// https://blog.naver.com/zbqmgldjfh/222453153459
// https://blog.naver.com/raylee00/222215714721



#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) x.begin(), x.end()
#define pb push_back

using ll = long long;
using pii = pair<int, int>;

// 세그먼트 트리 풀이. 9840KB 156ms
// 1-indexed 바텀업. 메모리 2n
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

int main()
{
    fastio;

    int n;
    cin >> n;

    vector<pii> arr(n);
    for (int i = 0; i < n; ++i)
    {
        int num;
        cin >> num;
        arr[i] = {num, i + 1};
    }
    sort(all(arr));

    ll ans = 0;
    SegTree<int> seg(n);
    for (const auto [num, idx] : arr)
    {
        ans += seg.Query(idx + 1, n);
        seg.Update(idx, 1);
    }

    cout << ans;
}



// 분할 정복, 병합 정렬 풀이 5932KB 112ms
/*
int arr[500'000];
int sorted[500'000];
ll ans = 0;

void Merge(int left, int mid, int right)
{
    int lo = left;
    int hi = mid + 1;
    int pivot = left;

    while (lo <= mid && hi <= right)
    {
        if (arr[lo] <= arr[hi])
        {
            sorted[pivot++] = arr[lo++];
        }
        else
        {
            sorted[pivot++] = arr[hi++];
            ans += mid - lo + 1;
        }
    }

    if (lo > mid)
    {
        for (int i = hi; i <= right; i++)
            sorted[pivot++] = arr[i];
    }
    else
    {
        for (int i = lo; i <= mid; i++)
            sorted[pivot++] = arr[i];
    }

    for (int i = left; i <= right; i++)
    {
        arr[i] = sorted[i];
    }
}

void MergeSort(int left, int right)
{
    if (left >= right) return;
    const int mid = (left + right) / 2;

    MergeSort(left, mid);
    MergeSort(mid + 1, right);
    Merge(left, mid, right);
}


int main()
{
    fastio;

    int n;
    cin >> n;

    for (int i = 0; i < n; ++i)
        cin >> arr[i];

    MergeSort(0, n - 1);
    cout << ans;
}
*/
