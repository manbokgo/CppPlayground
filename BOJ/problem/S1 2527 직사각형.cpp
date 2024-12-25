// URL: https://www.acmicpc.net/problem/2527
// Algo: 기하학

// Start:	241225 13 37
// Read:	0 2
// Think:	0 2
// Code:	0 5
// Total:	0 9

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

char AABB(Rect a, Rect b)
{
    // 겹치지 않음
    if ((a.left > b.right) ||
        (a.bottom > b.top) ||
        (a.right < b.left) ||
        (a.top < b.bottom))
        return 'd';

    // 점
    if ((a.left == b.right) && (a.bottom == b.top) ||
        (a.right == b.left) && (a.bottom == b.top) ||
        (a.left == b.right) && (a.top == b.bottom) ||
        (a.right == b.left) && (a.top == b.bottom))
        return 'c';

    // 선
    if ((a.left == b.right) || (a.right == b.left) ||
        (a.bottom == b.top) || (a.top == b.bottom))
        return 'b';

    return 'a';
}

int main()
{
    fastio;

    for (int i = 0; i < 4; ++i)
    {
        Rect a, b;
        cin >> a.left >> a.bottom >> a.right >> a.top;
        cin >> b.left >> b.bottom >> b.right >> b.top;
        cout << AABB(a, b) << '\n'; 
    }
}
