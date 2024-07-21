// URL: https://www.acmicpc.net/problem/10165
// Algo: 그리디, 스위핑

// Start:	240721 17 15
// Read:	0 2
// Think:	0 17
// Code:	0 8
// Total:   0 27

// 전형적인 스위핑 문제지만 원형이라는 것이 난점이다.
// st > en 일때의 처리가 중요한데 [9, 4]라면 [-1, 4]로 볼 수도 있고, [9, 14]로도 볼 수 있다.
// 두 가능성을 모두 추가하여 스위핑 돌리면 됨

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) x.begin(), x.end()
#define pb push_back

struct BusInfo
{
    int st;
    int en;
    int idx;
};

int main()
{
    fastio;

    int n, m;
    cin >> n >> m;

    vector<bool> good(m + 1);
    vector<BusInfo> buses;
    buses.reserve(m * 2);
    for (int i = 1; i <= m; ++i)
    {
        int st, en;
        cin >> st >> en;
        if (st < en)
        {
            buses.pb({st, en, i});
        }
        else
        {
            buses.pb({st - n, en, i});
            buses.pb({st, en + n, i});
        }
    
    }

    // 시작 오름차순 - 끝 내림차순
    sort(all(buses), [](const BusInfo a, const BusInfo b)
    {
        return a.st != b.st ? a.st < b.st : a.en > b.en;
    });

    int cur = 0;
    good[buses[cur].idx] = true;
    for (int i = 1; i < buses.size(); ++i)
    {
        if (buses[i].en > buses[cur].en)
        {
            good[buses[i].idx] = true;
            cur = i;
        }
    }

    for (int i = 1; i <= m; ++i)
    {
        if (good[i]) cout << i << ' ';
    }
}
