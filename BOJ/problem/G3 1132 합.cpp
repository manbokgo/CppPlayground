// URL: https://www.acmicpc.net/problem/1132
// Algo: 그리디

// Start:	240629 17 50
// Read:	0 2
// Think:	0 6
// Code:	0 20
// Total:	0 28

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) x.begin(), x.end()
#define pb push_back

using ll = long long;
constexpr ll LLINF = 1e18;

ll digit[10];
bool noZero[10];

int main()
{
    fastio;

    int n;
    cin >> n;

    for (int i = 0; i < n; ++i)
    {
        string tmp;
        cin >> tmp;
        noZero[tmp[0] - 'A'] = true;

        ll dg = 1;
        for (int j = tmp.size() - 1; j >= 0; --j)
        {
            digit[(tmp[j] - 'A')] += dg;
            dg *= 10;
        }
    }

    bool allUse = true;
    for (int i = 0; i < 10; ++i)
    {
        if (digit[i] == 0)
        {
            allUse = false;
            break;
        }
    }

    if (allUse)
    {
        ll mn = LLINF;
        int idx = -1;
        for (int i = 0; i < 10; ++i)
        {
            if (noZero[i] || digit[i] == 0) continue;
            if (mn > digit[i])
            {
                mn = digit[i];
                idx = i;
            }
        }
        digit[idx] = 0;
    }


    sort(begin(digit), end(digit));

    ll answer = 0;
    for (int i = 9; i >= 0; --i)
    {
        if (digit[i] == 0) break;
        answer += digit[i] * i;
    }
    cout << answer;
}
