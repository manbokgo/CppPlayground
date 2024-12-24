// URL: https://www.acmicpc.net/problem/10266
// Algo: KMP

// Start:	241224 10 10
// Read:	0 3
// Think:	0 25
// Code:	0 5
// Total:	0 33

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) x.begin(), x.end()
#define pb push_back

vector<int> Failure(const vector<bool>& s)
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


vector<bool> S(720'000);
vector<bool> P(360'000);

int main()
{
    fastio;

    int n;
    cin >> n;

    for (int i = 0; i < n; i++)
    {
        int x;
        cin >> x;
        S[x] = S[x + 360'000] = true;
    }

    for (int i = 0; i < n; i++)
    {
        int x;
        cin >> x;
        P[x] = true;
    }

    const vector<int> fail = Failure(P);

    vector<int> results;
    int j = 0;
    for (int i = 0; i < S.size(); i++)
    {
        while (j > 0 && S[i] != P[j])
            j = fail[j - 1];

        if (S[i] == P[j])
        {
            ++j;
            if (j == P.size())
            {
                cout << "possible";
                return 0;
            }
        }
    }

    cout << "impossible";
}
