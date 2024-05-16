// URL: https://school.programmers.co.kr/learn/courses/30/lessons/92345
// Algo: DFS 백트래킹

// Start:	240411 19 44
// Read:	0 2
// Think:	0 4
// Code:	0 21
// Total:	0 27

// 5x5 타일밖에 안 되고, 사라진 발판으로는 못 가는만큼 완전탐색 백트래킹하면 된다고 판단함

// 4방향으로 DFS를 호출해서 만약 내가 이길 수 있는 경우가 있다면 그 중 최솟값으로
// 절대 이길 수 없다면 최대한 끌어야하니 최댓값을 반환해야함

#include <vector>

using namespace std;
constexpr int INF = 0x3f3f3f3f;

int n, m;
bool OOB(int y, int x) {return y < 0 || y >= n || x < 0 || x >= m;}

using pbi = pair<bool, int>;
using pii = pair<int, int>;
int dy[4] = {-1, 0, 1, 0};
int dx[4] = {0, 1, 0, -1}; // 북동남서

pbi DFS(vector<vector<int>>& board, pii aloc, pii bloc, bool aturn, int depth)
{
    auto [y, x] = aturn ? aloc : bloc;
    if (!board[y][x])
        return {!aturn, depth};
    
    bool noWay = true;
    int cDist = INF, eDist = -1;
    for (int i = 0; i < 4; ++i)
    {
        int ny = y + dy[i];
        int nx = x + dx[i];
        if (OOB(ny, nx) || !board[ny][nx]) continue;
        noWay = false;

        board[y][x] = 0;
        if (aturn)
        {
            auto [aWin, dist] = DFS(board, {ny, nx}, bloc, false, depth + 1);
            if (aWin)
                cDist = min(cDist, dist);
            else
                eDist = max(eDist, dist);
        }
        else
        {
            auto [aWin, dist] = DFS(board, aloc, {ny, nx}, true, depth + 1);
            if (!aWin)
                cDist = min(cDist, dist);
            else
                eDist = max(eDist, dist);
        }
        board[y][x] = 1;
    }

    if (noWay)
        return {!aturn, depth};
    
    if (cDist != INF) 
        return {aturn, cDist};
    else
        return {!aturn, eDist};
}


int solution(vector<vector<int>> board, vector<int> aloc, vector<int> bloc) {
    n = board.size();
    m = board[0].size();
    
    auto [aWin, dist] = DFS(board, {aloc[0], aloc[1]}, {bloc[0], bloc[1]}, true, 0);
    return dist;
}
