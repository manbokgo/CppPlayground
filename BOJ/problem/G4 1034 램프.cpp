// URL: https://www.acmicpc.net/problem/1034
// Algo: 애드 혹

// Start:	240811 09 42
// Read:	0 2
// Think:	0 36
// Code:	0 5
// Total:	0 43

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) x.begin(), x.end()
#define pb push_back

unordered_map<string, int> um;

int main()
{
    fastio;
    int n, m;
    cin >> n >> m;

    for (int i = 0; i < n; ++i)
    {
        string tmp;
        cin >> tmp;
        ++um[tmp];
    }

    int k;
    cin >> k;

    int answer = 0;
    for (const auto& [pattern, cnt] : um)
    {
        int zeroCnt = 0;
        for (const auto c : pattern)
            if (c == '0') ++zeroCnt;

        if (zeroCnt <= k && zeroCnt % 2 == k % 2)
            answer = max(answer, cnt);
    }

    cout << answer;
}
