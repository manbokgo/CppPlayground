// URL: https://www.acmicpc.net/problem/2110
// Algo: 이분 탐색 + 매개변수 탐색

// Start:	240210 23 40
// Read:	0 1
// Think:	0 52
// Code:	0 16
// Total:	1 09

#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define X first
#define Y second
#define all(x) x.begin(), x.end()
#define sortvec(x) sort(all(x))
#define compress(x) x.erase(unique(all(x)), x.end())
#define findvec(x, value) find(all(x), value) != x.end()

using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;

constexpr ll  MOD = 1000000007;
constexpr int INF = 0x3f3f3f3f;
constexpr ll  LLINF = 1e18;

int n, c;
int arr[200'005];

// 0번째부터 시작하여, 직전에 확정된 공유기와 최소 dist 거리 이상인 다음 공유기를 찾는 것을 반복하여
// 가능한만큼 설치할 수 있는 공유기 수 count를 구함.
// 최소 dist가 클수록 count가 작아지므로 매개변수 탐색으로
// count가 n인, 최소 dist가 '최대인' 경우를 찾을 수 있음
bool solve(int dist)
{
    int last = arr[0];
    int count = 1; // 0번째 공유기는 확정 설치

    for (int i = 1; i < n; ++i)
    {
        if (arr[i] - last >= dist)
        {
            ++count;
            last = arr[i];
        }
    }

    // 이왕 정렬한거 이분탐색 O(log n)으로 순회해도 됨
    // 그러나 n이 겨우 20만이라 O(n)이랑 실제 시간에 아무 차이 없었고
    // 전체 시간복잡도는 정렬 O(n log n) 때문에 변함없음
    /*
    int lastIdx = 0;
    while (true)
    {
        auto it = lower_bound(arr + lastIdx, arr + n, last + dist);
        lastIdx = it - arr;
        if (lastIdx == n) break; // 이래서 벡터를 써야..

        ++count;
        last = *it;
    }
    */

    return count >= c;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> c;
    for (int i = 0; i < n; ++i)
    {
        cin >> arr[i];
    }

    sort(arr, arr + n);

    int st = 1;
    // dist의 이론적 최댓값은 공유기 양끝 거리에서 c-1등분한 값의 내림
    // 시간복잡도적으로는 그냥 10억 때려넣어도 무방함. 시간 8ms 줄임. 상수 시간 최적화.
    int en = (arr[n - 1] - arr[0]) / (c - 1);
    while (st < en)
    {
        int mid = (st + en + 1) / 2;
        if (solve(mid)) st = mid; // count가 n 이상이라면 최소 dist 정답은 현재 이상임
        else en = mid - 1;
    }

    cout << st;
}
