// URL: https://www.acmicpc.net/problem/1806
// Algo: 투 포인터

// Start:	240606 05 57
// Read:	0 1
// Think:	0 0
// Code:	0 3
// Total:	0 4

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) x.begin(), x.end()
#define pb push_back

constexpr int INF = 0x3f3f3f3f;

int arr[100'000];

int main()
{
    fastio;
    int n, target;
    cin >> n >> target;
    for (int i = 0; i < n; ++i)
        cin >> arr[i];

    int st = 0;
    int en = 0;
    int sum = arr[0];
    int answer = INF;
    while (st <= en && en < n)
    {
        if (sum >= target)
        {
            answer = min(answer, en - st + 1);
            sum -= arr[st];
            ++st;
        }
        else
        {
            ++en;
            sum += arr[en];
        }
    }

    if (answer == INF) answer = 0;
    cout << answer;
}
