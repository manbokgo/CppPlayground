// URL: https://www.acmicpc.net/problem/1799
// Algo: 백트래킹, 밋 인 더 미들

// Start:	240603 07 28
// Read:	0 1
// Think:	0 5
// Code:	0 5
// Think:	0 10
// Code:	0 5
// Total:	0 26
// 오모시로이
// https://manbokgo.notion.site/G1-1799-C-f53b58695fac42ea8ab0e0284e2fe647?pvs=74

// 10*10 칸에서 '모든 조합' 백트래킹은 O(2^(n*n)) = O(2^100) 으로 시간 초과다.
// 단, 대각선에는 비숍을 중복으로 놓을 수 없는 이 문제에선 최종적으로 배치 불가능한 칸이 최소 n*n/2 칸이기 때문에
// 대략적인 시간 복잡도는 O(2^(n*n/2)) = O(2^50) 이다. 마찬가지로 시간 초과다.
// https://www.acmicpc.net/board/view/68546#comment-117045

// 비숍은 검은칸 비숍과 하얀칸 비숍이 절대 서로를 침범할 수 없으니
// 밋 인 더 미들 테크닉처럼 백트래킹을 50칸, 50칸으로 절반을 뚝 나눌 수 있다.

// 검은칸 비숍들의 최대 개수 + 하얀칸 비숍들의 최대 개수
// 시간 복잡도 O(2^(n*n/2 / 2)) = O(2^25)로 가능해짐

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) x.begin(), x.end()
#define pb push_back

int n;
bool board[10][10];
bool fSlash[19];
bool bSlash[19];
int answer = -1;

void BackTracking(int y, int x, int sum)
{
    if (x >= n)
    {
        ++y;
        if (x % 2 == 0) x = 1;
        else x = 0;
    }

    if (y == n)
    {
        answer = max(answer, sum);
        return;
    }

    if (!board[y][x])
    {
        BackTracking(y, x + 2, sum);
        return;
    }

    const int fIdx = x + y;
    const int bIdx = (n - 1) + (x - y);
    if (fSlash[fIdx] || bSlash[bIdx])
    {
        BackTracking(y, x + 2, sum);
        return;
    }

    fSlash[fIdx] = bSlash[bIdx] = true;
    BackTracking(y, x + 2, sum + 1); // 놓기
    fSlash[fIdx] = bSlash[bIdx] = false;
    BackTracking(y, x + 2, sum); // 안 놓기
}

int main()
{
    fastio;
    cin >> n;
    for (int y = 0; y < n; ++y)
    {
        for (int x = 0; x < n; ++x)
        {
            cin >> board[y][x];
        }
    }

    BackTracking(0, 0, 0);
    BackTracking(0, 1, answer);
    cout << answer;
}
