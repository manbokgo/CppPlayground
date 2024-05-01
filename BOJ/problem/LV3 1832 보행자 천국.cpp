// URL: https://school.programmers.co.kr/learn/courses/30/lessons/1832
// Algo: DP, DFS

// Start:	240501 20 22
// Read:	0 1
// Think:	0 4
// Code:	0 21
// Total:	0 26

#include <vector>
#include <cstring>

using namespace std;

constexpr int MOD = 20170805;
constexpr int dy[2] = {0, -1};
constexpr int dx[2] = {-1, 0};

int tile[500][500];
int m, n;

int DFS(int y, int x, int ldir, const vector<vector<int>>& city_map)
{
    if (tile[y][x] != -1) return tile[y][x];
    
    if (city_map[y][x] == 1) return 0;
    if (city_map[y][x] == 2)
    {
        int ny = y + dy[ldir];
        int nx = x + dx[ldir];
        if (ny < 0 || ny >= m || nx < 0 || nx >= n) return 0;
        return DFS(ny, nx, ldir, city_map);
    }
    
    tile[y][x] = 0;
    for (int dir = 0; dir < 2; ++dir)
    {   
        int ny = y + dy[dir];
        int nx = x + dx[dir];
        if (ny < 0 || ny >= m || nx < 0 || nx >= n) continue;
        tile[y][x] += DFS(ny, nx, dir, city_map) % MOD;
    }
    return tile[y][x] % MOD;
}

int solution(int mI, int nI, vector<vector<int>> city_map) {
    m = mI; n = nI;
    memset(tile, -1, sizeof(tile));
    tile[0][0] = 1;
    return DFS(m-1, n-1, -1, city_map);
}