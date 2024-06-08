// URL: https://www.acmicpc.net/problem/1918
// Algo: 스택

// Start:	240609 07 14
// Read:	0 2
// Think:	0 21
// Code:	0 13
// Total:	0 36

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) x.begin(), x.end()
#define pb push_back

int main()
{
    fastio;
    stack<char> S;

    char c;
    while (cin >> c)
    {
        switch (c)
        {
        case '(':
            S.push(c);
            break;
        case ')':
            while (!S.empty())
            {
                const char tmp = S.top();
                S.pop();
                if (tmp == '(') break;
                cout << tmp;
            }
            break;
        case '+':
        case '-':
            while (!S.empty())
            {
                const char tmp = S.top();
                if (tmp == '(') break;
                S.pop();
                cout << tmp;
            }
            S.push(c);
            break;
        case '*':
        case '/':
            while (!S.empty())
            {
                const char tmp = S.top();
                if (tmp == '(') break;
                if (tmp == '+' || tmp == '-') break;
                S.pop();
                cout << tmp;
            }
            S.push(c);
            break;
        default:
            cout << c;
            break;
        }
    }

    while (!S.empty())
    {
        const char tmp = S.top();
        S.pop();
        cout << tmp;
    }
}
