// URL: https://www.acmicpc.net/problem/1339
// Algo: 그리디

// Start:	241125 09 51
// Read:	0 1
// Think:	0 4
// Code:	0 3
// Total:	0 8

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) x.begin(), x.end()
#define pb push_back

int sum[26];

int main()
{
    fastio;

    int n;
    cin >> n;

    string str;
    while (n--)
    {
        cin >> str;

        int val = 1;
        for (int i = str.size() - 1; i >= 0; --i)
        {
            sum[str[i] - 'A'] += val;
            val *= 10;
        }
    }
    sort(sum, sum + 26, greater<>());

    int ans = 0;
    int num = 9;
    for (int i = 0; i < 26; ++i)
    {
        ans += sum[i] * num;
        --num;
        if (num == 0) break;
    }

    cout << ans;
}
