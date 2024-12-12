// URL: https://www.acmicpc.net/problem/15973
// Algo: 기하학

// Start:	241212 18 55
// Read:	0 2
// Think:	0 5
// Code:	0 18
// Total:	0 25

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) x.begin(), x.end()
#define pb push_back

struct Rect
{
    int left;
    int bottom;
    int right;
    int top;
};

int main()
{
    fastio;

    Rect a, b;
    cin >> a.left >> a.bottom >> a.right >> a.top
        >> b.left >> b.bottom >> b.right >> b.top;

    if (a.left > b.left) swap(a, b);

    int h = -1;
    if (a.right < b.left) h = 0;
    else if (a.right == b.left) h = 1;
    else h = 2;


    if (a.bottom > b.bottom) swap(a, b);

    int v = -1;
    if (a.top < b.bottom) v = 0;
    else if (a.top == b.bottom) v = 1;
    else v = 2;


    if (h == 2 && v == 2) cout << "FACE";
    else if (h == 2 && v == 1) cout << "LINE";
    else if (h == 1 && v == 2) cout << "LINE";
    else if (h == 1 && v == 1) cout << "POINT";
    else cout << "NULL";
}
