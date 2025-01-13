// URL: https://www.acmicpc.net/problem/1991
// Algo: 트리

// Start:	250114 07 29
// Read:	0 1
// Think:	0 1
// Code:	0 3
// Total:	0 5

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) x.begin(), x.end()
#define pb push_back

char child[26][2];

void PreOrder(char cur)
{
    if (cur == '.') return;

    cout << cur;
    PreOrder(child[cur - 'A'][0]);
    PreOrder(child[cur - 'A'][1]);
}

void InOrder(char cur)
{
    if (cur == '.') return;

    InOrder(child[cur - 'A'][0]);
    cout << cur;
    InOrder(child[cur - 'A'][1]);
}

void PostOrder(char cur)
{
    if (cur == '.') return;

    PostOrder(child[cur - 'A'][0]);
    PostOrder(child[cur - 'A'][1]);
    cout << cur;
}

int main()
{
    fastio;

    int n;
    cin >> n;

    while (n--)
    {
        char p, l, r;
        cin >> p >> l >> r;
        child[p - 'A'][0] = l;
        child[p - 'A'][1] = r;
    }

    PreOrder('A');
    cout << '\n';
    InOrder('A');
    cout << '\n';
    PostOrder('A');
}
