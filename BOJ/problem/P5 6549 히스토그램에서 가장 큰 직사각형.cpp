// URL: https://www.acmicpc.net/problem/6549
// Algo: 세그먼트 트리 변형 (바텀업 arr), 분할 정복 or 스택

// Start:	241120 07 03
// Read:	0 1
// Think:	0 21
// Code:	0 18
// Total:	0 40
// 오모시로이

// 세그먼트 트리에 저장하는 값을 그 구간에서의 최소높이 '인덱스'로 한다.
// 이후 분할 정복으로 피벗(구간 내 최소높이)으로 구한 전체 구간 넓이와
// 피벗 좌우 구간의 넓이 중 큰 걸 찾아낸다. 8286KB 56ms

// 사실 단순하게 스택만 이용해서 풀 수도 있다. 스택에 들어간 막대는 오른쪽으로 얼마나 확장될 수 있는지를 기다린다.
// 만약 이전 막대보다 작은 막대가 들어오면(오름차순이 깨지면) 현재 막대보다 더 큰 이전 막대는
// 현재 막대 직전까지만 오른쪽으로 확장할 수 있으니 넓이를 계산할 수 있다.
//
// 다시 스택이 오름차순이 될 때까지 스택에서 pop을 하며
// 현재 막대 직전 ~ pop한 막대 구간의 면적 넓이를 구한다. 2940KB 32ms

// 좀 복잡하긴 하지만 분할 정복만 이용해서도 풀 수 있다.

// https://codable.tistory.com/1

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) x.begin(), x.end()
#define pb push_back

using ll = long long;

// 세그먼트 트리 풀이 8286KB 56ms
template <typename T>
class SegTree
{
    int n;
    T defVal;

    vector<T> arr;
    vector<T> seg;

    int func(int a, int b)
    {
        if (a == -1) return b;
        if (b == -1) return a;
        return arr[a] <= arr[b] ? a : b;
    }

public:
    explicit SegTree(const vector<T>& arr, T defVal = T{})
        : n(arr.size()),
          defVal(defVal),
          arr(arr)
    {
        seg.resize(2 * n, defVal);
        for (int i = 0; i < n; ++i)
            seg[i + n] = i;

        for (int i = n - 1; i > 0; i--) // O(n)
            seg[i] = func(seg[i * 2], seg[i * 2 + 1]);
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

    ll GetAnswer()
    {
        return GetAnswer(0, n - 1);
    }

    ll GetAnswer(int st, int en)
    {
        const int pivot = Query(st, en);
        ll areaSz = 1LL * (en - st + 1) * arr[pivot];

        if (st < pivot) areaSz = max(areaSz, GetAnswer(st, pivot - 1));
        if (pivot < en) areaSz = max(areaSz, GetAnswer(pivot + 1, en));
        return areaSz;
    }
};

int main()
{
    fastio;

    int n;
    while (true)
    {
        cin >> n;
        if (n == 0) break;

        vector<int> arr(n);
        for (auto& num : arr) cin >> num;

        SegTree<int> seg(arr, -1);
        cout << seg.GetAnswer() << '\n';
    }
}

// 스택 풀이 2940KB 32ms
/*
int arr[100'000];

int main()
{
    fastio;

    int n;
    while (true)
    {
        cin >> n;
        if (n == 0) break;

        for (int i = 0; i < n; ++i)
            cin >> arr[i];
        arr[n] = -1; // 남은 스택 처리용

        stack<int> S;
        ll ans = 0;
        for (int i = 0; i <= n; ++i)
        {
            // 이전 막대보다 작은 막대가 들어오면(오름차순이 깨지면)
            // pop을 하며 스택이 다시 오름차순이 되는 곳까지의 구간 넓이를 계산한다
            while (!S.empty() && arr[S.top()] > arr[i])
            {
                const int h = arr[S.top()];
                S.pop();

                const int w = S.empty() ? i : i - S.top() - 1;
                ans = max(ans, 1LL * h * w);
            }
            S.push(i);
        }
        cout << ans << '\n';
    }
}
*/
