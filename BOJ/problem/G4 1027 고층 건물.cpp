// URL: https://www.acmicpc.net/problem/1027
// Algo: 브루트포스, 기하학

// Start:	240727 17 16
// Read:	0 2
// Think:	0 18
// Code:	0 4
// Total:	0 24

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) x.begin(), x.end()
#define pb push_back

int arr[50];
int cnt[50];

int main()
{
    fastio;

    int n;
    cin >> n;
    for (int i = 0; i < n; ++i)
        cin >> arr[i];

    for (int i = 0; i < n; ++i)
    {
        double mx = -5e9;
        for (int j = i + 1; j < n; ++j)
        {
            double slope = (double)(arr[j] - arr[i]) / (j - i);
            if (mx < slope)
            {
                mx = slope;
                ++cnt[i];
                ++cnt[j];
            }
        }
    }

    cout << *max_element(cnt, cnt + n);
}
