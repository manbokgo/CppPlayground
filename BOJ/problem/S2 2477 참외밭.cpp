// URL: https://www.acmicpc.net/problem/2477
// Algo: 기하학

// Start:	241203 17 01
// Read:	0 2
// Think:	0 10
// Code:	0 7
// Total:	0 19

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) x.begin(), x.end()
#define pb push_back

struct info
{
    int dir;
    int len;
};

info arr[6];
int cnt[5];

int main()
{
    fastio;

    int k;
    cin >> k;

    for (auto& [dir, len] : arr)
    {
        cin >> dir >> len;
        ++cnt[dir];
    }

    int big = 1;
    int small = 1;
    for (int i = 0; i < 6; ++i)
    {
        // 한 번만 등장하는 방향은 큰 사각형의 너비/높이다.
        if (cnt[arr[i].dir] == 1)
        {
            big *= arr[i].len;
            continue;
        }

        // i와 i+2의 방향이 같다면, i+1이 작은 사각형의 너비/높이다.
        if (arr[i].dir == arr[(i + 2) % 6].dir)
        {
            small *= arr[(i + 1) % 6].len;
        }
    }
    cout << k * (big - small);
}
