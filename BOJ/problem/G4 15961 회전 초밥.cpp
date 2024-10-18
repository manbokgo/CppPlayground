// URL: https://www.acmicpc.net/problem/15961
// Algo: 슬라이딩 윈도우

// Start:	241019 06 55
// Read:	0 1
// Think:	0 1
// Code:	0 15
// Total:	0 17

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) x.begin(), x.end()
#define pb push_back

int main()
{
    fastio;

    int n, d, k, c;
    cin >> n >> d >> k >> c;

    vector<int> arr(n);
    for (int i = 0; i < n; ++i)
        cin >> arr[i];

    vector<int> sushi(d + 1);

    int answer = 0;
    int cnt = 0;
    int st = 0;
    int en = k - 1;
    for (int i = st; i <= en; ++i)
    {
        if (!sushi[arr[i]])
        {
            ++cnt;
        }
        ++sushi[arr[i]];
    }

    if (!sushi[c]) answer = max(answer, cnt + 1);
    else answer = max(answer, cnt);

    while (true)
    {
        --sushi[arr[st]];
        if (sushi[arr[st]] == 0) --cnt;

        ++st;
        if (st == n) break;

        ++en;
        if (en == n) en = 0;

        if (sushi[arr[en]] == 0) ++cnt;
        ++sushi[arr[en]];

        if (!sushi[c]) answer = max(answer, cnt + 1);
        else answer = max(answer, cnt);
    }

    cout << answer;
}
