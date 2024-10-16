// URL: https://www.acmicpc.net/problem/17619
// Algo: 스위핑 or 분리 집합

// Start:	241016 20 05
// Read:	0 1
// Think:	0 4
// Code:	0 10
// Total:	0 15

// y 좌표는 아무 의미 없다. 스위핑으로 통나무마다 그룹번호를 매기는 대신, 분리 집합을 사용해도 된다.

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) x.begin(), x.end()
#define pb push_back

using tiii = tuple<int, int, int>;

int main()
{
    fastio;

    int n, q;
    cin >> n >> q;

    vector<tiii> lines;
    lines.reserve(n);

    for (int i = 0; i < n; ++i)
    {
        int a, b, c;
        cin >> a >> b >> c;
        lines.pb({a, b, i});
    }
    sort(all(lines));

    vector<int> group(n);
    int groupIdx = 0;

    auto [cSt, cEn, cIdx] = lines[0];
    group[cIdx] = groupIdx;

    for (int i = 1; i < n; ++i)
    {
        const auto [st, en, idx] = lines[i];

        if (st > cEn) ++groupIdx;
        cEn = max(cEn, en);
        group[idx] = groupIdx;
    }

    while (q--)
    {
        int a, b;
        cin >> a >> b;
        --a;
        --b;
        cout << (group[a] == group[b]) << '\n';
    }
}
