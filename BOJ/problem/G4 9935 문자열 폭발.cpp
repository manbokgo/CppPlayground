// URL: https://www.acmicpc.net/problem/9935
// Algo: 문자열

// Start:	241108 17 34
// Read:	0 1
// Think:	0 2
// Code:	0 7
// Total:	0 10

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) x.begin(), x.end()
#define pb push_back

int main()
{
    fastio;

    string str, explode;
    cin >> str >> explode;
    const size_t expSz = explode.size();

    string answer;
    answer.reserve(str.size());
    for (const char c : str)
    {
        answer += c;
        if (answer.size() < expSz) continue;
        if (answer.back() == explode.back())
        {
            string tmp = answer.substr(answer.size() - expSz, expSz);
            if (tmp == explode)
                answer.erase(answer.size() - expSz);
        }
    }

    if (answer.empty()) cout << "FRULA";
    else cout << answer;
}
