// URL: https://www.acmicpc.net/problem/2143
// Algo: 누적 합, 이분 탐색 or 해시 맵

// Start:	240913 14 04
// Read:	0 3
// Think:	0 2
// Code:	0 8
// Total:	0 13

// 이렇게 모든 가능한 누적 합을 구하는 문제면, 내가 푼 것처럼 누적 합을 구한 후 빼기를 하는 것보다는
// 숫자만 받고 누적 합을 구하는 게 연산이 더 적다.

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) x.begin(), x.end()
#define pb push_back

using ll = long long;

int sumN[1'001];
int sumM[1'001];

int main()
{
    fastio;

    int t;
    cin >> t;

    int n;
    cin >> n;
    for (int i = 1; i <= n; ++i)
    {
        cin >> sumN[i];
        sumN[i] += sumN[i - 1];
    }

    int m;
    cin >> m;
    for (int i = 1; i <= m; ++i)
    {
        cin >> sumM[i];
        sumM[i] += sumM[i - 1];
    }

    // 이분 탐색 사용
    vector<int> cntN;
    cntN.reserve(n);
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 0; j < i; ++j)
        {
            cntN.pb(sumN[i] - sumN[j]);
        }
    }
    sort(all(cntN));

    ll answer = 0;
    for (int i = 1; i <= m; ++i)
    {
        for (int j = 0; j < i; ++j)
        {
            const int target = t - (sumM[i] - sumM[j]);
            answer += upper_bound(all(cntN), target) - lower_bound(all(cntN), target);
        }
    }
    cout << answer;

    // 해시 맵 사용
    /*
    unordered_map<int, int> cntN;
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 0; j < i; ++j)
        {
            ++cntN[sumN[i] - sumN[j]];
        }
    }

    ll answer = 0;
    for (int i = 1; i <= m; ++i)
    {
        for (int j = 0; j < i; ++j)
        {
            const int target = t - (sumM[i] - sumM[j]);
            if (cntN.count(target)) answer += cntN[target];
        }
    }

    cout << answer;
    */
}
