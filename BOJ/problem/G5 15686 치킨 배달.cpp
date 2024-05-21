// URL: https://www.acmicpc.net/problem/15686
// Algo: 브루트포스, 조합

// Start:	240521 19 46
// Read:	0 2
// Think:	0 2
// Code:	0 8
// Total:	0 12

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) x.begin(), x.end()
#define pb push_back

constexpr int INF = 0x3f3f3f3f;
using pii = pair<int, int>;

int n, m;
vector<pii> houses;
vector<pii> chickens;

int main()
{
    fastio;
    cin >> n >> m;

    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            int num;
            cin >> num;
            if (num == 1) houses.pb({i, j});
            else if (num == 2) chickens.pb({i, j});
        }
    }

    vector<bool> sel(chickens.size());
    for (int i = 0; i < m; ++i)
    {
        sel[i] = true;
    }

    int answer = INF;
    do
    {
        int sum = 0;
        for (const auto [y, x] : houses)
        {
            int mn = INF;
            for (int i = 0; i < chickens.size(); ++i)
            {
                if (!sel[i]) continue;
                const auto [ny, nx] = chickens[i];
                mn = min(mn, abs(y - ny) + abs(x - nx));
            }
            sum += mn;
        }
        answer = min(answer, sum);
    }
    while (prev_permutation(all(sel)));

    cout << answer;
}
