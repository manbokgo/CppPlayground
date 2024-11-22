// URL: https://www.acmicpc.net/problem/12904
// Algo: 그리디

// Start:	241123 07 51
// Read:	0 1
// Think:	0 3
// Code:	0 2
// Total:	0 6

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) x.begin(), x.end()
#define pb push_back

int main()
{
    fastio;

    string S, T;
    cin >> S >> T;

    while (S.size() != T.size())
    {
        if (T.back() == 'A')
        {
            T.pop_back();
        }
        else
        {
            T.pop_back();
            reverse(all(T));
        }
    }

    cout << (S == T);
}
