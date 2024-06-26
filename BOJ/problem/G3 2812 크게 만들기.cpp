// URL: https://www.acmicpc.net/problem/2812
// Algo: 그리디, 스택

// Start:	240627 08 41
// Read:	0 1
// Think:	0 5
// Code:	0 6
// Total:	0 12

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

    string num;
    string ans;
    num.reserve(n);
    ans.reserve(n);

    cin >> num;
    for (int i = 0; i < n; ++i)
    {
        while (!ans.empty() && num[i] > ans.back() && k)
        {
            ans.pop_back();
            --k;
        }
        ans.push_back(num[i]);
    }

    while (k--) ans.pop_back();
    cout << ans;
}
