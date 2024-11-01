// URL: https://www.acmicpc.net/problem/1695
// Algo: DP

// Start:	241101 18 00
// Read:	0 1
// Think:	0 11
// Code:	0 3
// Total:   0 15

// 1 2 3 4 2 에서  st 0, en 4이어서 1과 2를 비교할 때,
// A. 1의 앞에 2를 끼워넣어 st 0(1), en 3(4)을 비교하는 경우 dp[0][3]
// B. 2의 뒤에 1을 끼워넣어 st 1(2), en 4(2)를 비교하는 경우 dp[1][4]
// 둘 중 dp 값이 작은 경우에 +1한 것이 dp[0][4]가 된다.

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) x.begin(), x.end()
#define pb push_back

int arr[5'000];
int dp[5'000][5'000]; // st ~ en 범위에서 팰린드롬이 되기 위한 최소 수

int Solve(int st, int en)
{
    if (st >= en) return 0;
    if (dp[st][en] != -1) return dp[st][en];
    if (arr[st] == arr[en]) return dp[st][en] = Solve(st + 1, en - 1);
    return dp[st][en] = min(Solve(st, en - 1), Solve(st + 1, en)) + 1;
}

int main()
{
    fastio;
    memset(dp, -1, sizeof(dp));

    int n;
    cin >> n;

    for (int i = 0; i < n; ++i)
        cin >> arr[i];

    cout << Solve(0, n - 1);
}
