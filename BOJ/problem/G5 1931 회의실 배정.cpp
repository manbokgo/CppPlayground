// URL: https://www.acmicpc.net/problem/1931
// Algo: 그리디

// Start:	250121 09 41
// Read:	0 1
// Think:	0 3
// Code:	0 2
// Total:	0 6

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) x.begin(), x.end()
#define pb push_back

using pii = pair<int, int>;

pii arr[100'000];

int main()
{
    fastio;

    int n;
    cin >> n;

    for (int i = 0; i < n; i++)
        cin >> arr[i].second >> arr[i].first;

    sort(arr, arr + n);

    int ans = 0;
    int en = 0;
    for (int i = 0; i < n; i++)
    {
        if (en <= arr[i].second)
        {
            en = arr[i].first;
            ans++;
        }
    }
    cout << ans;
}
