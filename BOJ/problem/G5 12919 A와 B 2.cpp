// URL: https://www.acmicpc.net/problem/12919
// Algo: 브루트포스, 재귀

// Start:	241209 06 39
// Read:	0 1
// Think:	0 8
// Code:	0 7
// Total:	0 16

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) x.begin(), x.end()
#define pb push_back

string S, T;

void Solve(string t)
{
    if (S == t)
    {
        cout << 1;
        exit(0);
    }

    if (S.size() >= t.size()) return;

    if (t.back() == 'A')
    {
        Solve(t.substr(0, t.size() - 1));
    }

    if (t.front() == 'B')
    {
        reverse(all(t));
        Solve(t.substr(0, t.size() - 1));
    }
}


int main()
{
    fastio;

    cin >> S >> T;

    Solve(T);
    cout << 0;
}
