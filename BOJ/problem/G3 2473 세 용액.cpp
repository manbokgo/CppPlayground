// URL: https://www.acmicpc.net/problem/2473
// Algo: 투 포인터

// Start:	240809 09 42
// Read:	0 2
// Think:	0 5
// Code:	0 5
// Total:	0 12

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) x.begin(), x.end()
#define pb push_back

using ll = long long;
constexpr ll LLINF = 1e18;

int main()
{
    fastio;
    int n;
    cin >> n;

    vector<int> arr(n);
    for (auto& num : arr) cin >> num;
    sort(all(arr));

    ll mn = LLINF;
    int answer[3];
    for (int i = 0; i < n - 2; ++i)
    {
        int st = i + 1;
        int en = n - 1;
        while (st < en)
        {
            ll sum = (ll)arr[i] + arr[st] + arr[en];
            if (mn > abs(sum))
            {
                mn = abs(sum);
                answer[0] = arr[i];
                answer[1] = arr[st];
                answer[2] = arr[en];
            }

            if (sum > 0) --en;
            else ++st;
        }
    }

    cout << answer[0] << ' ' << answer[1] << ' ' << answer[2];
}
