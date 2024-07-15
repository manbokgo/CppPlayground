// URL: https://www.acmicpc.net/problem/16120
// Algo: 스택

// Start:	240716 13 31
// Read:	0 3
// Think:	0 1
// Code:	0 3
// Total:	0 7

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) x.begin(), x.end()
#define pb push_back

int main()
{
    fastio;
    string str;
    cin >> str;

    string tmp;
    tmp.reserve(str.size());

    for (const char c : str)
    {
        tmp += c;
        int sz = tmp.size();
        if (sz < 4) continue;

        if (tmp[sz - 4] == 'P' && tmp[sz - 3] == 'P' && tmp[sz - 2] == 'A' && tmp[sz - 1] == 'P')
        {
            tmp.pop_back();
            tmp.pop_back();
            tmp.pop_back();
            tmp.pop_back();
            tmp += 'P';
        }
    }

    if (tmp.size() == 1 && tmp[0] == 'P') cout << "PPAP";
    else cout << "NP";
}
