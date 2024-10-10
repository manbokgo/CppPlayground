// URL: https://www.acmicpc.net/problem/14391
// Algo: 브루트포스, 비트마스킹

// Start:	241010 17 23
// Read:	0 2
// Think:	0 34
// Code:	0 12
// Total:	0 48

// 모든 경우의 수를 탐색해야 하는 문제란 것 자체는 바로 알아챔
// 처음엔 백트래킹으로 해야하나 싶었다가 너무 복잡한 것 같아서, 좀 생각하다보니
// 최대 4x4칸이라는 것을 보고 O(2^n) 풀이라고 생각해서 비트마스킹 문제란 걸 알아냄

// 특정 자리의 bit가 그 타일을 0이면 가로, 1이면 세로로 쪼개는 걸 의미한다.

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) x.begin(), x.end()
#define pb push_back

int board[4][4];

int main()
{
    fastio;

    int n, m;
    cin >> n >> m;

    for (int y = 0; y < n; ++y)
    {
        for (int x = 0; x < m; ++x)
        {
            char c;
            cin >> c;
            board[y][x] = c - '0';
        }
    }

    int answer = 0;
    for (int bit = 0; bit < (1 << (n * m)); ++bit)
    {
        int sum = 0;

        // 가로
        for (int y = 0; y < n; y++)
        {
            int cur = 0;
            for (int x = 0; x < m; x++)
            {
                const int idx = y * m + x;
                if (!(bit & (1 << idx)))
                {
                    cur = cur * 10 + board[y][x];
                }
                else
                {
                    sum += cur;
                    cur = 0;
                }
            }
            sum += cur;
        }

        // 세로
        for (int x = 0; x < m; x++)
        {
            int cur = 0;
            for (int y = 0; y < n; y++)
            {
                const int idx = y * m + x;
                if (bit & (1 << idx))
                {
                    cur = cur * 10 + board[y][x];
                }
                else
                {
                    sum += cur;
                    cur = 0;
                }
            }
            sum += cur;
        }

        answer = max(answer, sum);
    }
    cout << answer;
}
