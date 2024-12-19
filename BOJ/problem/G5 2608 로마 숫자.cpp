// URL: https://www.acmicpc.net/problem/2608
// Algo: 구현

// Start:	241220 05:05
// Read:	0 3
// Think:	0 5
// Code:	0 10
// Total:	0 18

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) x.begin(), x.end()
#define pb push_back

map<char, int> roman = {
    {'I', 1},
    {'V', 5},
    {'X', 10},
    {'L', 50},
    {'C', 100},
    {'D', 500},
    {'M', 1000}
};

int main()
{
    fastio;

    string a, b;
    cin >> a >> b;

    int sum = 0;
    for (int i = 0; i < a.size(); i++)
    {
        if (i + 1 < a.size() && roman[a[i]] < roman[a[i + 1]])
            sum -= roman[a[i]];
        else
            sum += roman[a[i]];
    }

    for (int i = 0; i < b.size(); i++)
    {
        if (i + 1 < b.size() && roman[b[i]] < roman[b[i + 1]])
            sum -= roman[b[i]];
        else
            sum += roman[b[i]];
    }

    cout << sum << '\n';

    string answer;
    while (sum > 0)
    {
        if (sum >= 1000)
        {
            answer += 'M';
            sum -= 1000;
        }
        else if (sum >= 900)
        {
            answer += "CM";
            sum -= 900;
        }
        else if (sum >= 500)
        {
            answer += 'D';
            sum -= 500;
        }
        else if (sum >= 400)
        {
            answer += "CD";
            sum -= 400;
        }
        else if (sum >= 100)
        {
            answer += 'C';
            sum -= 100;
        }
        else if (sum >= 90)
        {
            answer += "XC";
            sum -= 90;
        }
        else if (sum >= 50)
        {
            answer += 'L';
            sum -= 50;
        }
        else if (sum >= 40)
        {
            answer += "XL";
            sum -= 40;
        }
        else if (sum >= 10)
        {
            answer += 'X';
            sum -= 10;
        }
        else if (sum >= 9)
        {
            answer += "IX";
            sum -= 9;
        }
        else if (sum >= 5)
        {
            answer += 'V';
            sum -= 5;
        }
        else if (sum >= 4)
        {
            answer += "IV";
            sum -= 4;
        }
        else
        {
            answer += 'I';
            sum -= 1;
        }   
    }

    cout << answer;
}
