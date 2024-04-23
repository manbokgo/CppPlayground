// URL: https://school.programmers.co.kr/learn/courses/30/lessons/60061
// Algo: 시뮬레이션

// Start:	240423 21 00
// Read:	0 3
// Think:	0 2
// Code:	1 0 폰코딩 크아아악
// Total:	1 5

// CanOne 조건 하나 빠뜨린 걸 알아차리지 못하고, Validate 함수 만들어보기도 했는데
// 조건만 안 빠졌으면 처음부터 맞는 거였다

#include <vector>

using namespace std;
int n;
vector<vector<int>> tile;

// 보
bool CanTwo(int x, int y) {
    return (tile[x][y-1] & 1) || 
           (tile[x+1][y-1] & 1) ||
           (x < n-1 && tile[x+1][y] & 2 && x > 0 && tile[x-1][y] & 2);
}

// 기둥
bool CanOne(int x, int y) {
    return (y == 0) || 
           (tile[x][y] & 2) || // 실수: 이 조건 깜빡해서 30분 헤맴
           (x > 0 && tile[x-1][y] & 2) ||
           (tile[x][y-1] & 1);
}

// 필요 없는 함수
bool Validate(int x, int y)
{
    if (x < 0 || x > n || y < 0 || y > n) return true;
    return !(
                (tile[x][y] & 1 && !CanOne(x, y) ) ||
                (tile[x][y] & 2 && !CanTwo(x, y) )
            );
}

vector<vector<int>> solution(int nIn, vector<vector<int>> build_frame) {
    n = nIn;
    tile.resize(n+1, vector<int>(n+1));
    for (const auto& frm : build_frame) {
        int x = frm[0];
        int y = frm[1];
        int a = frm[2];
        int b = frm[3];
        
        if (b) {
            if (a) {
                if (CanTwo(x, y))
                    tile[x][y] |= 2;
            }
            else {
                if (CanOne(x, y))
                    tile[x][y] |= 1;
            }
        }
        else {
            if (a) {
                tile[x][y] &= ~2;
                // if (!( Validate(x, y) && Validate(x-1, y) && Validate(x+1, y) ))
                if (
                    (tile[x][y] & 1 && !CanOne(x, y)) ||
                    (tile[x+1][y] & 1 && !CanOne(x+1, y)) ||
                    (x < n-1 && tile[x+1][y] & 2 && !CanTwo(x+1, y)) ||
                    (x > 0 && tile[x-1][y] & 2 && !CanTwo(x-1, y))
                )
                    tile[x][y] |= 2;                   
            }
            else {
                tile[x][y] &= ~1;
                // if (!( Validate(x, y + 1) && Validate(x-1, y + 1) ))
                if (
                    (tile[x][y+1] & 2 && !CanTwo(x, y+1)) ||
                    (y < n-1 && tile[x][y+1] & 1 && !CanOne(x, y+1)) ||
                    (x > 0 && tile[x-1][y+1] & 2 && !CanTwo(x-1, y+1))
                )
                    tile[x][y] |= 1;     
            }
        }
    }
    
    vector<vector<int>> answer;
    for (int x = 0; x <= n; ++x)
        for (int y = 0; y <= n; ++y) {
            if (tile[x][y] & 1)
                answer.push_back({x, y, 0});
            if (tile[x][y] & 2)
                answer.push_back({x, y, 1});
        }    
    
    return answer;
}