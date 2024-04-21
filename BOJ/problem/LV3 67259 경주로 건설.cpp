// URL: https://school.programmers.co.kr/learn/courses/30/lessons/67259
// Algo: BFS, 완전 탐색, DP

// Start:	240422 02 12
// Read:	0 3
// Think:	0 3
// Code:	0 44
// Total:	0 50
// 오모시로이

// 백준 G3 6087 레이저 통신과 유사하지만 더 까다롭다.
// 레이저 통신 문제를 다익스트라로 (아름답지 못하게) 푸는 방법에서 '타일 진입 방향'을 고려해야 했던 것처럼,
// 이 문제도 어떤 타일을 → 방향으로 진입했냐, ↓ 방향으로 진입했냐에 따라 비용이 다르며
// 방향별로 구해지는 비용 중 최소 값을 구하는게 핵심이다.

// 처음엔 막연하게 코너를 더 많이 돌더라도 비용이 더 적은 경우가 있지 않을까 의심하면서
// 레이저 통신 풀이처럼 직선 개수만을 고려하는 식으로 제출했는데 일부 테케에서 틀리는 걸 보고 확신함

// 구체적으로 어떤 경우에 코너가 더 많지만 비용이 적을까, 그러면 어떻게 처리해야할까 생각하며 몸 비틀다가
// 어떤 타일을 다른 방향으로 진입했는데 그 비용이 더 작다면, 한번 더 큐에 넣어서 돌려보면 되겠네? 하는 아이디어로 풀음.
// 한 타일이 큐에 여러 번 들어가서 벽에 닿을 때까지 4방향 탐색하지만 25x25 타일 밖에 안 되므로 성능적인 문제는 없다.
// 다만 0.1ms 미만으로 테케 다 통과해서 정답 뜨고서도 이게 최선이었나? 하며 굉장히 찜찜했음

// 정석적인 방법은 board[y][x][direction] 으로 DP를 사용하는 것.
// 이렇게 하면 동일 방향인데 비용이 더 작은 타일을 발견했을 때 바로 탐색을 종료할 수 있어 더 효율적이다.


// 제출 코드 정답
#include <queue>
#include <vector>

using namespace std;
using pii = pair<int, int>;

int dy[4] = {0, 1, 0, -1};
int dx[4] = {1, 0, -1, 0}; // 동남서북

int n;
bool OOB(int y, int x) { return y < 0 || y >= n || x < 0 || x >= n; }

int solution(vector<vector<int>> board) {
    n = board.size();
    queue<pii> q;
    q.push({0,0});
    board[0][0] = -500;
    
    while (!q.empty())
    {
        auto [y, x] = q.front(); q.pop();
        for (int i = 0; i < 4; ++i)
        {
            int ny = y + dy[i];
            int nx = x + dx[i];
            int newCost = board[y][x] + 500 + 100;
            
            while (!OOB(ny, nx) && board[ny][nx] != 1)
            {
                // 큰 의미 없다
                // if (board[ny][nx] > 0 && board[ny][nx] + 500 <= newCost) break;
                if (board[ny][nx] == 0 || board[ny][nx] > newCost)
                {
                    board[ny][nx] = newCost;
                    q.push({ny, nx});
                }
                
                ny += dy[i];
                nx += dx[i];
                newCost += 100;
            }
        }
    }
    
    return board[n-1][n-1];
}