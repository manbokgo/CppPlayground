// URL: https://www.acmicpc.net/problem/16637
// Algo: 브루트포스

// Start:	240924 18 10
// Read:	0 1
// Think:	0 6
// Code:	0 14
// Total:	0 21

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) x.begin(), x.end()
#define pb push_back

int n;
string str;

int Calc(int a, char c, int b)
{
    if (c == '+') return a + b;
    if (c == '-') return a - b;
    if (c == '*') return a * b;
}

int DFS(int cur, int sum)
{
    if (cur >= n) return sum;

    int ret = DFS(cur + 2, Calc(sum, str[cur], str[cur + 1] - '0')); // 괄호 X
    if (cur + 2 < n)
    {
        const int bracket = Calc(str[cur + 1] - '0', str[cur + 2], str[cur + 3] - '0');
        ret = max(ret, DFS(cur + 4, Calc(sum, str[cur], bracket))); // 괄호 O
    }
    return ret;
}

int main()
{
    fastio;
    cin >> n >> str;
    cout << DFS(1, str[0] - '0');
}
