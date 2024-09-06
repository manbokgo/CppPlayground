// URL: https://www.acmicpc.net/problem/1644
// Algo: 에라토스테네스의 체, 투 포인터

// Start:	240906 18 30
// Read:	0 1
// Think:	0 1
// Code:	0 12
// Total:	0 14

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) x.begin(), x.end()
#define pb push_back

int main()
{
    fastio;

    int n;
    cin >> n;

    // 에라토스테네스의 체
    vector<bool> nums(n + 1, true);
    vector<int> primes;

    for (int i = 2; i * i <= n; ++i)
    {
        if (!nums[i]) continue;
        for (int j = i * i; j <= n; j += i)
            nums[j] = false;
    }

    for (int i = 2; i <= n; ++i)
        if (nums[i]) primes.pb(i);


    if (primes.empty())
    {
        cout << 0;
        return 0;
    }

    int st = 0;
    int en = 0;
    int sum = primes[0];
    int answer = 0;
    while (en < primes.size())
    {
        if (sum == n) ++answer;

        if (sum >= n)
        {
            sum -= primes[st];
            ++st;
        }
        else
        {
            ++en;
            if (en == primes.size()) break;
            sum += primes[en];
        }
    }
    cout << answer;
}
