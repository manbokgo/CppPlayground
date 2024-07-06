// URL: https://www.acmicpc.net/problem/10986
// Algo: 누적 합

// Start:	240706 08 00
// Read:	0 2
// Think:	0 18
// Code:	0 10
// Total:	0 30

// 1-Based 인덱스일 때, 구하려고 하는 쌍 (i,j)은 (sum[j] - sum[i-1]) % M = 0 이다
// 식을 변형하면 sum[j] % M = sum[i-1] % M 이므로
// % M 한 값들이 같은 것들의 쌍의 수를 모두 세면 됨  xC2  (0<=x<m)

// arr[0], sum[0]에는 0이 들어갈 것이므로 mod[0]은 기본적으로 1이 더해져야함
// 이래야만 (1,j)의 쌍들까지 제대로 구해진다

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) x.begin(), x.end()
#define pb push_back

using ll = long long;

int main()
{
    fastio;

    int n, m;
    cin >> n >> m;

    ll sum = 0;
    vector<ll> mod(m);
    ++mod[0]; // sum[0] = 0
    for (int i = 1; i <= n; ++i)
    {
        ll num;
        cin >> num;
        sum += num;
        ++mod[sum % m];
    }

    ll answer = 0;
    for (int i = 0; i < m; ++i)
        answer += mod[i] * (mod[i] - 1) / 2;

    cout << answer;
}
