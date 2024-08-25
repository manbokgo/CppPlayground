// URL: https://www.acmicpc.net/problem/2015
// Algo: 누적 합, 맵

// Start:	240814 09 02
// Read:	0 2
// Think:	0 7
// Code:	0 12
// Total:	0 21

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) x.begin(), x.end()
#define pb push_back

using ll = long long;

int sum[200'001];
unordered_map<ll, ll> um;

int main()
{
    fastio;

    int n, k;
    cin >> n >> k;

    um[0] = 1;

    ll answer = 0;
    for (int i = 1; i <= n; ++i)
    {
        cin >> sum[i];
        sum[i] += sum[i - 1];

        answer += um[sum[i] - k];
        ++um[sum[i]];
    }
    cout << answer;
}
