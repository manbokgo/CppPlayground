// URL: https://www.acmicpc.net/problem/12100
// Algo: 시뮬레이션, 백트래킹

// Start:	
// Read:	0 1
// Think:	0 1
// Code:	0 24
// Total:	0 26

// while 루프에서 dy, dx를 이용하여 블록의 최종 위치를 찾아가는 식으로 풀었다 MoveMethod 8ms
// 깔끔하지만, 이번 턴에 합쳐진 블럭은 또 합쳐지지 않도록 merged 배열로 따로 체크해야 함

// 이 문제는 중간에 벽이 있거나 하지 않은만큼, 이동 후 반드시 한 쪽 끝으로 차곡차곡 블럭이 쌓이게 되니
// 최종 위치 인덱스를 두고 블록이 그 위치에 채워질 때마다 인덱스를 늘리거나 줄이거나 하는 식으로 하면
// merged 배열도 필요없고 효율적이다. PosMethod 0ms
// 단, 4방향 각각이 코드가 달라서 깔끔하진 않음

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) x.begin(), x.end()
#define pb push_back

int n;
int dy[4] = {0, 0, 1, -1};
int dx[4] = {1, -1, 0, 0}; // 동서남북
bool OOB(int y, int x) { return y < 0 || y >= n || x < 0 || x >= n; }
int board[20][20];
bool merged[20][20];
int answer = 0;

void Move(int dir, int y, int x)
{
    if (board[y][x] == 0) return;

    const int num = board[y][x];
    board[y][x] = 0;

    int ny = y;
    int nx = x;
    while (true)
    {
        ny += dy[dir];
        nx += dx[dir];

        if (OOB(ny, nx))
        {
            ny -= dy[dir];
            nx -= dx[dir];
            board[ny][nx] = num;
            break;
        }

        if (board[ny][nx] == num && !merged[ny][nx])
        {
            board[ny][nx] *= 2;
            merged[ny][nx] = true;
            break;
        }

        if (board[ny][nx] != 0)
        {
            ny -= dy[dir];
            nx -= dx[dir];
            board[ny][nx] = num;
            break;
        }
    }
}

void MoveMethod(int dir)
{
    switch (dir)
    {
    case 0: // 동
        for (int x = n - 1; x >= 0; --x)
            for (int y = 0; y < n; ++y)
                Move(dir, y, x);
        break;
    case 1: // 서
        for (int x = 0; x < n; ++x)
            for (int y = 0; y < n; ++y)
                Move(dir, y, x);
        break;
    case 2: // 남
        for (int y = n - 1; y >= 0; --y)
            for (int x = 0; x < n; ++x)
                Move(dir, y, x);
        break;
    case 3: // 북
        for (int y = 0; y < n; ++y)
            for (int x = 0; x < n; ++x)
                Move(dir, y, x);
        break;
    default: ;
    }
}

void PosMethod(int dir)
{
    switch (dir)
    {
    case 0: // 동
        for (int y = 0; y < n; ++y)
        {
            int xPos = n - 1;
            for (int x = n - 2; x >= 0; --x)
            {
                if (board[y][x] == 0) continue;
                const int num = board[y][x];
                board[y][x] = 0;

                if (board[y][xPos] == num)
                {
                    board[y][xPos] *= 2;
                    --xPos;
                    continue;
                }

                if (board[y][xPos] != 0) --xPos;
                board[y][xPos] = num;
            }
        }
        break;
    case 1: // 서
        for (int y = 0; y < n; ++y)
        {
            int xPos = 0;
            for (int x = 1; x < n; ++x)
            {
                if (board[y][x] == 0) continue;
                const int num = board[y][x];
                board[y][x] = 0;

                if (board[y][xPos] == num)
                {
                    board[y][xPos] *= 2;
                    ++xPos;
                    continue;
                }

                if (board[y][xPos] != 0) ++xPos;
                board[y][xPos] = num;
            }
        }
        break;
    case 2: // 남
        for (int x = 0; x < n; ++x)
        {
            int yPos = n - 1;
            for (int y = n - 2; y >= 0; --y)
            {
                if (board[y][x] == 0) continue;
                const int num = board[y][x];
                board[y][x] = 0;

                if (board[yPos][x] == num)
                {
                    board[yPos][x] *= 2;
                    --yPos;
                    continue;
                }

                if (board[yPos][x] != 0) --yPos;
                board[yPos][x] = num;
            }
        }
        break;

    case 3: // 북
        for (int x = 0; x < n; ++x)
        {
            int yPos = 0;
            for (int y = 1; y < n; ++y)
            {
                if (board[y][x] == 0) continue;
                const int num = board[y][x];
                board[y][x] = 0;

                if (board[yPos][x] == num)
                {
                    board[yPos][x] *= 2;
                    ++yPos;
                    continue;
                }

                if (board[yPos][x] != 0) ++yPos;
                board[yPos][x] = num;
            }
        }
        break;
    default: ;
    }
}

void DFS(int depth)
{
    if (depth == 5)
    {
        for (int y = 0; y < n; ++y)
            for (int x = 0; x < n; ++x)
                if (answer < board[y][x]) answer = board[y][x];

        return;
    }

    int tmp[20][20];
    memcpy(tmp, board, sizeof(board));
    for (int dir = 0; dir < 4; ++dir)
    {
        // while 루프로 최종 위치 찾아가기 8ms
        MoveMethod(dir);

        // 차곡차곡 쌓이는만큼 최종 위치 인덱스 사용 0ms
        // PosMethod(dir);

        DFS(depth + 1);
        memcpy(board, tmp, sizeof(board));
    }
}

int main()
{
    fastio;
    cin >> n;
    for (int y = 0; y < n; ++y)
        for (int x = 0; x < n; ++x)
            cin >> board[y][x];

    DFS(0);
    cout << answer;
}
