// URL: https://www.acmicpc.net/problem/1114
// Algo: 이분 탐색, 매개변수 탐색

// Start:	240701 22 45
// Read:	0 2
// Think:	0 19
// Code:	0 42
// Total:   1 3

// mid의 최솟값을 구해야하는 FFFFFTTTT 매개변수 탐색
// 모든 조각을 mid 길이 이하로 자르는 횟수 cnt가 c 이하라면 TRUE, 초과면 FALSE
// mid가 작아질수록 cnt가 커져서 F쪽으로 가므로, 가장 mid가 작은 T를 구할 수 있음

// 가장 앞 자르는 위치를 반환해야 하는만큼, 내림차순으로 위치를 정렬해야함

// 양끝과, 자르는 위치 사이사이의 최대 길이보다 더 작게 자를 수는 없으므로 st는 maxGap
// 이걸 안 하면 mid 바뀔 때마다 사이사이 길이가 mid보다 큰 지 검사해야하므로 귀찮아짐

// 만약 모든 조각을 mid 길이 이하로 잘랐는데 더 자를 수 있다면
// 가장 앞 위치를 추가로 자를 수 있다 (반례:  5 2 5   1 2   정답 3 1)

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) x.begin(), x.end()
#define pb push_back

constexpr int INF = 0x3f3f3f3f;

int main()
{
    fastio;

    int l, k, c;
    cin >> l >> k >> c;
    vector<int> arr(k);
    for (int i = 0; i < k; ++i)
        cin >> arr[i];

    arr.erase(unique(all(arr)), arr.end());
    sort(all(arr), greater<>());

    int maxGap = max(l - arr[0], arr[k - 1]);
    for (int i = 0; i < k - 1; ++i)
        maxGap = max(maxGap, arr[i] - arr[i + 1]);

    int st = maxGap;
    int en = l;
    int answer = arr[0];
    while (st < en)
    {
        const int mid = (st + en) / 2;

        int lastCut = l;
        int cnt = 0;

        for (int i = 0; i < k; ++i)
        {
            if (lastCut - arr[i] > mid)
            {
                lastCut = arr[i - 1];
                ++cnt;
            }
        }
        if (lastCut - 0 > mid)
        {
            lastCut = arr[k - 1];
            ++cnt;
        }

        // 더 자를 수 있다면 가장 앞을 또 자른다
        if (cnt < c) lastCut = arr[k - 1];

        if (cnt <= c)
        {
            en = mid;
            answer = lastCut;
        }
        else
        {
            st = mid + 1;
        }
    }

    cout << st << ' ' << answer;
}
