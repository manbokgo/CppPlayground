// URL: https://www.acmicpc.net/problem/1052
// Algo: 그리디, 비트마스킹

// Start:	241227 06 40
// Read:	0 2
// Think:	0 10
// Code:	0 5
// Total:	0 17

// n을 이진수로 표현했을 때 비트 수가 최대한 합친 후의 물병 개수를 의미한다.
// 13 = 1101(2)  8 + 4 + 1 로 3개의 물병이 된다. 만약 3이 k보다 크다면, 비트 수를 줄여야하므로
// 최하위 비트를 더하는 것을 반복하여 k개 이하의 비트를 가지도록 만든다.

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) x.begin(), x.end()
#define pb push_back

int main()
{
    fastio;

    int n, k;
    cin >> n >> k;

    int answer = 0;
    while (bitset<32>(n).count() > k) // n의 비트 중 1의 개수가 k보다 클 때
    {
        const int diff = n & (~n + 1); // n의 최하위 비트
        n += diff;
        answer += diff;
    }
    cout << answer;
}
