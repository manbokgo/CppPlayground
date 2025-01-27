// URL: https://www.acmicpc.net/problem/11003
// Algo: 슬라이딩 윈도우, 덱

// Start:	250127 15 00
// Read:	0 1
// Think:	0 3
// Code:	0 3
// Total:	0 7

// LV3 64062 징검다리 건너기 문제에서 흥미로워서 알아보았던 Sliding Window Maximum 방법 O(n)을 이용한 문제
// https://velog.io/@rmswjdtn/%EC%8A%AC%EB%9D%BC%EC%9D%B4%EB%94%A9-%EC%9C%88%EB%8F%84%EC%9A%B0-Leet-code-239.-Sliding-Window-Maximum
// https://ansohxxn.github.io/boj/11003/

// 1. Deque의 뒤에서부터 원소를 집어넣는다.
// 2. Deque의 앞 원소가 지금 집어넣을 원소에서 왼쪽으로 k 범위 안에 없다면, pop_front()
// 3. Deque의 뒷 원소가 지금 집어넣을 원소보다 '크'다면, pop_back()  
// 4. Deque의 앞 원소가 현재 슬라이딩 윈도우의 최솟값이다.

// 핵심은 덱에 최솟값이 될 수 있는 후보 숫자들만 남겨놓는 것.
// 3번 과정에서 절대 최솟값이 될 수 없는 것들을 빼주는 게 핵심이다.

// 사실 우선순위 큐 O(nlogn)로 범위를 벗어나가는 top을 보이는대로 빼주는 식으로 해도 풀리긴 한다.

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) x.begin(), x.end()
#define pb push_back

using pii = pair<int, int>;

int main()
{
    fastio;

    int n, k;
    cin >> n >> k;

    deque<pii> dq; // {값, 인덱스}
    for (int i = 1; i <= n; ++i)
    {
        int num;
        cin >> num;

        while (!dq.empty() && dq.front().second < i - k + 1) dq.pop_front();
        while (!dq.empty() && dq.back().first > num) dq.pop_back();
        dq.push_back({num, i});
        cout << dq.front().first << ' ';
    }
}
