// URL: https://www.acmicpc.net/problem/2655
// Algo: DP

// Start:	240915 14 06
// Read:	0 1
// Think:	0 1
// Code:	0 36
// Total:	0 38

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) x.begin(), x.end()
#define pb push_back

using tiiii = tuple<int, int, int, int>;

int n;
int dp[101];
int nxt[101];
tiiii boxes[101];

int Solve(int num)
{
    if (dp[num] != -1) return dp[num];

    const auto& [bottom, height, weight, idx] = boxes[num];

    dp[num] = 0;
    for (int i = num + 1; i <= n; ++i)
    {
        const auto& [nBottom, nHeight, nWeight, nIdx] = boxes[i];
        if (weight < nWeight) continue;

        const int result = Solve(i);
        if (dp[num] < result)
        {
            dp[num] = result;
            nxt[num] = i;
        }
    }
    dp[num] += height;

    return dp[num];
}


int main()
{
    fastio;
    memset(dp, -1, sizeof(nxt));
    memset(nxt, -1, sizeof(nxt));

    cin >> n;
    for (int i = 1; i <= n; ++i)
    {
        auto& [bottom, height, weight, idx] = boxes[i];
        cin >> bottom >> height >> weight;
        idx = i;
    }
    sort(boxes + 1, boxes + 1 + n, greater<>());

    int mxHeight = 0;
    int cur = 0;
    for (int i = 1; i <= n; ++i)
    {
        const int nowHeight = Solve(i);
        if (mxHeight < nowHeight)
        {
            mxHeight = nowHeight;
            cur = i;
        }
    }

    vector<int> answer;
    while (cur != -1)
    {
        const auto& [bottom, height, weight, idx] = boxes[cur];
        answer.pb(idx);
        cur = nxt[cur];
    }

    cout << answer.size() << '\n';
    for (auto it = answer.rbegin(); it != answer.rend(); ++it)
    {
        cout << *it << '\n';
    }
}
