// URL: https://www.acmicpc.net/problem/2457
// Algo: 그리디

// Start:	240707 11 48
// Read:	0 2
// Think:	0 5
// Code:	0 18
// Total:	0 25

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) x.begin(), x.end()
#define pb push_back

using pii = pair<int, int>;

int main()
{
    fastio;

    int mToD[] = {0, 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30};
    for (int i = 1; i <= 12; ++i)
        mToD[i] += mToD[i - 1];

    int n;
    cin >> n;

    vector<pii> flowers(n);

    int mxEn = -1;
    for (int i = 0; i < n; ++i)
    {
        int stM, stD, enM, enD;
        cin >> stM >> stD >> enM >> enD;

        const int st = mToD[stM] + stD;
        const int en = mToD[enM] + enD;
        flowers[i] = {st, en};
        mxEn = max(mxEn, en);
    }
    sort(all(flowers));

    if (flowers[0].first > mToD[3] + 1 || mxEn < mToD[12] + 1)
    {
        cout << 0;
        return 0;
    }

    int cur = 0;
    for (int i = cur + 1; i < n; ++i)
    {
        const auto [st, en] = flowers[i];
        if (st > mToD[3] + 1) break;

        if (en > flowers[cur].second)
            cur = i;
    }

    int answer = 1;
    while (flowers[cur].second < mToD[12] + 1)
    {
        int mxIdx = cur;
        for (int i = cur + 1; i < n; ++i)
        {
            const auto [st, en] = flowers[i];
            if (st > flowers[cur].second) break;

            if (en > flowers[mxIdx].second)
                mxIdx = i;
        }

        if (mxIdx == cur)
        {
            cout << 0;
            return 0;
        }

        cur = mxIdx;
        ++answer;

    }
    cout << answer;
}
