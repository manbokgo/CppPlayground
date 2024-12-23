// URL: https://www.acmicpc.net/problem/20157
// Algo: 기하학, 해시 맵

// Start:	241223 09 03
// Read:	0 2
// Think:	0 4
// Code:	0 4
// Total:	0 10

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) x.begin(), x.end()
#define pb push_back

using pii = pair<int, int>;

map<pii, int> slope;

int main()
{
    fastio;

    int n;
    cin >> n;

    while (n--)
    {
        int x, y;
        cin >> x >> y;

        const int gc = gcd(x, y);
        ++slope[{x/ gc, y/ gc}];
    }

    int ans = 0;
    for (const auto& [_, cnt] : slope)
        ans = max(ans, cnt);

    cout << ans;
}
