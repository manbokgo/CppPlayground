// URL: https://www.acmicpc.net/problem/15684
// Algo: 백트래킹

// Start:	240724 22 22
// Read:	0 2
// Think:	0 4
// Code:	0 21
// Total:	0 27

// 백트래킹으로 2차원 좌표를 순회할 때, DFS 함수의 인자로 y,x 값 대신 idx를 넘겨서 y,x를 즉석해서 계산하고,
// 재귀를 반복하는 대신 for 루프를 돌려 재귀를 줄이는 식이 제일 성능이 좋았다.

// 0ms짜리 제출을 보니 실패한 백트래킹 이후 while (!ladders[i][j - 1] && !ladders[i][j + 1]) i++; 을 호출하는데
// 실패했던 위치 아래쪽 좌우에 사다리가 없는(변수가 없는) 모든 구간 내에 사다리를 두는 건, 실제적으로 동일한 결과를 내기 때문에
// 경우의 수를 대폭 감소시킬 수 있기 때문임.

// 예시:
// 1 ---|xx
// 2 xxx|xx
// 3 xxx|xx
// 4 xxx|--
// 5 xxx|xx
// 6 ---|xx

// 2에 놓고 실패했다면, 3에 놓아도 동일한 결과를 냄. 4는 불가능한 위치고, 5는 새로운 가능성임.

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) x.begin(), x.end()
#define pb push_back

int n, m, h;
int mxIdx = 0;
bool ladder[31][11];
int mxCnt = 0;

bool Go()
{
    for (int x = 1; x <= n; ++x)
    {
        const int st = x;
        for (int y = 1; y <= h; ++y)
        {
            if (ladder[y][x]) ++x;
            else if (ladder[y][x - 1]) --x;
        }

        if (x != st) return false;
    }

    return true;
}

void DFS(int cur, int cnt)
{
    if (cnt == 0)
    {
        if (Go())
        {
            cout << mxCnt;
            exit(0);
        }
        return;
    }

    for (int i = cur; i < mxIdx; ++i)
    {
        const int y = i / (n - 1) + 1;
        const int x = i % (n - 1) + 1;
        if (ladder[y][x] || ladder[y][x - 1] || ladder[y][x + 1]) continue;

        ladder[y][x] = true;
        DFS(i + 1, cnt - 1);
        ladder[y][x] = false;
    }
}

int main()
{
    fastio;
    cin >> n >> m >> h;
    mxIdx = h * (n - 1);
    while (m--)
    {
        int a, b;
        cin >> a >> b;
        ladder[a][b] = true;
    }

    for (; mxCnt <= 3; ++mxCnt) DFS(0, mxCnt);

    cout << -1;
}
