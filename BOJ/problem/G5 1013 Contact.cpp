// URL: https://www.acmicpc.net/problem/1013
// Algo: 정규 표현식

// Start:	241129 11 40
// Read:	0 2
// Think:	0 2
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

    int n;
    cin >> n;

    const regex pattern{"(100+1+|01)+"};
    string str;
    while (n--)
    {
        cin >> str;
        cout << (regex_match(str, pattern) ? "YES\n" : "NO\n");
    }
}
