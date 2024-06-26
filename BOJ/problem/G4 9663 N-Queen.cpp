﻿// URL: https://www.acmicpc.net/problem/9663
// Algo: 백트래킹

// Start:	240615 12 19
// Read:	0 1
// Think:	0 1
// Code:	0 6 시간초과
// Code:	0 10
// Total:	0 18

// G1 1799 비숍 문제와는 달리 동일한 행에는 더 이상 퀸을 놓을 수 없으며,
// 문제 조건상 '반드시 행당 하나의 퀸'이 존재해야 한다.
// 불필요한 재귀를 줄이면서 더 최적화해야지만 시간에 맞는다

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) x.begin(), x.end()
#define pb push_back

int n;
bool col[15];
bool fSlash[29];
bool bSlash[29];
int answer = 0;

void BackTracking(int y)
{
    if (y == n)
    {
        ++answer;
        return;
    }

    for (int x = 0; x < n; ++x)
    {
        const int fIdx = x + y;
        const int bIdx = (n - 1) + (x - y);
        if (col[x] || fSlash[fIdx] || bSlash[bIdx]) continue;
        col[x] = fSlash[fIdx] = bSlash[bIdx] = true;
        BackTracking(y + 1);
        col[x] = fSlash[fIdx] = bSlash[bIdx] = false;
    }
}


int main()
{
    fastio;
    cin >> n;

    BackTracking(0);
    cout << answer;
}
