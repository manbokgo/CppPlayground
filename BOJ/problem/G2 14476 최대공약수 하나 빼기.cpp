// URL: https://www.acmicpc.net/problem/14476
// Algo: 누적 합, 수학, GCD

// Start:	240630 20 48
// Read:	0 3
// Think:	0 42
// Code:	0 6
// Total:	0 51

// front[i] = arr[0] ~ arr[i]까지의 최대 공약수
// back[i] = arr[n-1] ~ arr[i]까지의 최대 공약수
// arr[i]를 제외했을 때, 남은 것들의 최대 공약수는 gcd(front[i-1], back[i+1)이다

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) x.begin(), x.end()
#define pb push_back

int _gcd(int a, int b)
{
    return b ? _gcd(b, a % b) : a;
}

int main()
{
    fastio;

    int n;
    cin >> n;

    vector<int> arr(n);
    for (int i = 0; i < n; ++i)
        cin >> arr[i];

    vector<int> front(n);
    vector<int> back(n);

    front[0] = arr[0];
    for (int i = 1; i < n; ++i)
        front[i] = gcd(arr[i], front[i - 1]);

    back[n - 1] = arr[n - 1];
    for (int i = n - 2; i >= 0; --i)
        back[i] = gcd(arr[i], back[i + 1]);

    int K = -1;
    int ans = -1;

    for (int i = 0; i < n; ++i)
    {
        int tmp;
        if (i == 0) tmp = back[i + 1];
        else if (i == n - 1) tmp = front[i - 1];
        else tmp = gcd(front[i - 1], back[i + 1]);

        if (arr[i] % tmp != 0 && ans < tmp)
        {
            ans = tmp;
            K = arr[i];
        }
    }

    cout << ans;
    if (ans != -1)
        cout << ' ' << K;
}
