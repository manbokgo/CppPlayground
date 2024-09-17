// URL: https://www.acmicpc.net/problem/27172
// Algo: 브루트포스, 에라토스테네스의 체

// Start:	240918 08 19
// Read:	0 2
// Think:	0 4
// Code:	0 3
// Total:	0 9

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) x.begin(), x.end()
#define pb push_back

int arr[100'000];
int score[1'000'001];
bool used[1'000'001];

int main()
{
    fastio;

    int n;
    cin >> n;
    for (int i = 0; i < n; ++i)
    {
        cin >> arr[i];
        used[arr[i]] = true;
    }

    for (int i = 0; i < n; ++i)
    {
        for (int j = arr[i] * 2; j <= 1'000'000; j += arr[i])
        {
            if (!used[j]) continue;
            --score[j];
            ++score[arr[i]];
        }
    }

    for (int i = 0; i < n; ++i)
    {
        cout << score[arr[i]] << ' ';
    }
}
