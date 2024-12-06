// URL: https://www.acmicpc.net/problem/3108
// Algo: 기하학, 분리 집합

// Start:	241206 14 26
// Read:	0 1
// Think:	0 14
// Code:	0 38
// Total:	0 53

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) x.begin(), x.end()
#define pb push_back

int p[1'001];

int Find(int a)
{
    if (p[a] < 0) return a;
    return p[a] = Find(p[a]);
}

bool Union(int a, int b)
{
    int ap = Find(a);
    int bp = Find(b);

    if (ap == bp) return false;
    if (-p[ap] < -p[bp]) swap(ap, bp);

    p[ap] += p[bp];
    p[bp] = ap;
    return true;
}


struct Rect
{
    int left;
    int bottom;
    int right;
    int top;
};

bool AABB(Rect a, Rect b)
{
    if ((a.left > b.right) ||
        (a.bottom > b.top) ||
        (a.right < b.left) ||
        (a.top < b.bottom))
        return false;

    // 포함
    if ((a.left < b.left) &&
        (a.bottom < b.bottom) &&
        (a.right > b.right) &&
        (a.top > b.top))
        return false;

    swap(a, b);
    if ((a.left < b.left) &&
        (a.bottom < b.bottom) &&
        (a.right > b.right) &&
        (a.top > b.top))
        return false;

    return true;
}

int main()
{
    fastio;
    memset(p, -1, sizeof(p));

    int n;
    cin >> n;

    vector<Rect> arr(n);
    for (auto& [left, bottom, right, top] : arr)
        cin >> left >> bottom >> right >> top;

    arr.push_back({0, 0, 0, 0});
    ++n;

    for (int i = 0; i < n; ++i)
    {
        for (int j = i + 1; j < n; ++j)
        {
            if (AABB(arr[i], arr[j]))
                Union(i, j);
        }
    }

    int answer = -1;
    for (int i = 0; i < n; ++i)
    {
        if (p[i] < 0) ++answer;
    }
    cout << answer;
}
