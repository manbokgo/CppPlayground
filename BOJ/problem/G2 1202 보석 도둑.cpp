// URL: https://www.acmicpc.net/problem/1202
// Algo: 그리디

// Start:	240515 17 36
// Read:	0 2
// Think:	0 12
// Code:	0 5 틀림
// Think:	0 8
// Code:	0 11
// Total:	0 38

// 쓸데없이 어렵게 생각했다. 풀고보니 골2라고 하기엔 쉬운 문제인데 머리가 안 돌아감.

// 보석무게 내림차순, 가방무게 내림차순으로 정렬하여 보석을 순회하며,
// 가방에 무거운 보석부터 채울 수 있을만큼 채운다.

// 만약 현재 보석 무게가 커서 현재 가방엔 넣을 순 없거나, 가방이 모두 꽉 찬 상황에서
// 기존에 넣었던 최솟값 가치의 보석보다 현재 보석 가치가 더 크다면, 이전 가방 속 보석을 대체하는 식.
// 가방무게가 내림차순이니 현재 보석은 반드시 이전 가방에 들어갈 수 있음.

// 그런데 로직상 더 직관적인 것은
// 보석무게 오름차순, 가방무게 오름차순으로 정렬하여 가방을 순회하며,
// 현재 가방무게 이하인 보석들을 몽땅 우선순위 큐에 넣고, 그 중 최대값을 뽑아서 현재 가방에 넣고 하는 식임.

// 이렇게 간단한 걸 왜 진작 생각 못 했지...
// 그나마 내 풀이는 '채울 수 있을만큼 채운다' 과정이 우선순위큐에서 최대값을 뽑는 것이 아니기 때문에
// 연산 횟수가 조금 더 작아서 시간이 좀 더 빠르다.  (184ms -> 132ms)

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);

constexpr int INF = 0x3f3f3f3f;

using ll = long long;
using pii = pair<int, int>;
pii jewels[300'000];
int packs[300'000];

int main()
{
    fastio;

    int n, k;
    cin >> n >> k;
    for (int i = 0; i < n; ++i)
    {
        auto& [m, v] = jewels[i];
        cin >> m >> v;
    }

    for (int i = 0; i < k; ++i)
    {
        cin >> packs[i];
    }

    // 보석무게 오름차순, 가방무게 오름차순 직관적풀이 184ms
    sort(jewels, jewels + n);
    sort(packs, packs + k);
    priority_queue<int> pq;

    ll ans = 0;
    int jIdx = 0;
    for (int i = 0; i < k; ++i)
    {
        const int w = packs[i];
        for (; jIdx < n; ++jIdx)
        {
            const auto [m, v] = jewels[jIdx];
            if (m > w) break;
            pq.push(v);
        }

        if (!pq.empty())
        {
            ans += pq.top();
            pq.pop();
        }
    }


    // 보석무게 내림차순, 가방무게 내림차순 제출풀이 132ms
    /*
    sort(jewels, jewels + n, greater<>());
    sort(packs, packs + k, greater<>());
    priority_queue<int, vector<int>, greater<>> pq;

    ll ans = 0;
    int pIdx = 0;
    for (int i = 0; i < n; ++i)
    {
        const auto [m, v] = jewels[i];
        if (pIdx < k && m <= packs[pIdx])
        {
            ++pIdx;
            ans += v;
            pq.push(v);
            continue;
        }

        if (!pq.empty())
        {
            int lowest = pq.top();
            if (v > lowest)
            {
                pq.pop();
                ans -= lowest;
                ans += v;
                pq.push(v);
            }
        }
    }
    */

    cout << ans;
}
