// URL: https://www.acmicpc.net/problem/1744
// Algo: 그리디

// Start:	240620 15 35
// Read:	0 2
// Think:	0 7
// Code:	0 8
// Total:	0 17

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) x.begin(), x.end()
#define pb push_back

vector<int> arrP;
vector<int> arrM;

// 0 x
// 1 x

int main()
{
    fastio;

    arrP.reserve(50);
    arrM.reserve(50);

    int n;
    cin >> n;
    for (int i = 0; i < n; ++i)
    {
        int num;
        cin >> num;
        if (num > 0) arrP.pb(num);
        else arrM.pb(num);
    }
    sort(all(arrP), greater<>());
    sort(all(arrM));

    int answer = 0;
    if (arrP.size() % 2 == 1)
    {
        answer += arrP.back();
        arrP.pop_back();
    }
    for (int i = 0; i < arrP.size(); i += 2)
    {
        if (arrP[i + 1] == 1) answer += arrP[i] + arrP[i + 1];
        else answer += arrP[i] * arrP[i + 1];
    }

    if (arrM.size() % 2 == 1)
    {
        answer += arrM.back();
        arrM.pop_back();
    }
    for (int i = 0; i < arrM.size(); i += 2)
    {
        answer += arrM[i] * arrM[i + 1];
    }

    cout << answer;
}
