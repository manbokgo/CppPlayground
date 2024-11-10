// URL: https://www.acmicpc.net/problem/1498
// Algo: KMP

// Start:	241110 17 52
// Read:	0 2
// Think:	0 39
// Code:	0 3
// Total:	0 44

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) x.begin(), x.end()
#define pb push_back

vector<int> Failure(const string& s)
{
    vector<int> f(s.size());

    int j = 0;
    for (int i = 1; i < s.size(); i++)
    {
        while (j > 0 && s[i] != s[j])
            j = f[j - 1];
        if (s[i] == s[j])
            f[i] = ++j;
    }
    return f;
}

int main()
{
    fastio;

    string str;
    cin >> str;

    const auto fail = Failure(str);

    for (int i = 1; i < fail.size(); ++i)
    {
        if (fail[i] == 0) continue;
        const int prefix = i + 1 - fail[i];
        if ((i + 1) % prefix == 0)
            cout << i + 1 << ' ' << (i + 1) / prefix << '\n';
    }
}
