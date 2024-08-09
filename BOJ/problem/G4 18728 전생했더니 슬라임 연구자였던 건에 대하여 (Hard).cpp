// URL: https://www.acmicpc.net/problem/14698
// Algo: 그리디

// Start:	240810 06 32
// Read:	0 4
// Think:	0 2
// Code:	0 20
// Total:	0 26

// 우선순위 큐에는 mod 하지 않은 원본 수가 들어가야 한다는 점을 놓치고 헤맴.
// 문제 조건에서 원본 둘의 곱이 2x10^18이 넘지 않는다고 달려있으니 오버플로의 걱정은 없다.

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) x.begin(), x.end()
#define pb push_back

using ll = long long;
constexpr ll MOD = 1000000007;

int main()
{
    fastio;
    int T;
    cin >> T;

    while (T--)
    {
        int n;
        cin >> n;

        priority_queue<ll, vector<ll>, greater<>> pq;
        while (n--)
        {
            ll num;
            cin >> num;
            pq.push(num);
        }

        ll answer = 1;
        while (pq.size() > 1)
        {
            const ll n1 = pq.top();
            pq.pop();
            const ll n2 = pq.top();
            pq.pop();

            const ll mul = n1 * n2;
            answer = (answer * (mul % MOD)) % MOD;
            pq.push(mul);
        }

        cout << answer << '\n';
    }
}
