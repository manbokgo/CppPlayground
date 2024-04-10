// URL: https://school.programmers.co.kr/learn/courses/30/lessons/92344
// Algo: 누적 합

// Start:	240411 03 13
// Read:	0 2
// Think:	0 27
// Code:	0 12
// Total:	0 41

// 아주 단순하게 매 스킬마다 board 각 요소를 업데이트한다면
// 최악 시간 복잡도는 O(1,000 x 1,000 x 250,000)로 뻑나갈 거 예상함
// 스킬 시작지점과 종료지점만 업데이트해야 한다는 점까지는 쉽게 생각했는데 누적합 떠올리는게 오래걸림

// n  0  0  -n
// 0  0  0  0
// 0  0  0  0
// -n 0  0  n
// 스킬 범위가 (0,0) ~ (2,2)면 위와 같이 (0,0), (3,3) 기준으로 4군데만 업데이트한다
// 열로 누적합하고, 행으로 누적합하면 (0,0) ~ (2,2)가 의도한대로 다 n으로 채워짐

#include <vector>

using namespace std;

int sum[1001][1001];

int solution(vector<vector<int>> board, vector<vector<int>> skill) {
    for (const auto& ski : skill)
    {
        int degree = ski[0] == 1 ? -ski[5] : ski[5];
        int r1 = ski[1], c1 = ski[2], r2 = ski[3], c2 = ski[4];
        
        sum[r1][c1] += degree;
        sum[r1][c2 + 1] -= degree;
        sum[r2 + 1][c1] -= degree;
        sum[r2 + 1][c2 + 1] += degree;
    }
    
    for (int x = 0; x < board[0].size(); ++x)
    {
        for (int y = 0; y < board.size(); ++y)
        {
            sum[y + 1][x] += sum[y][x];
        }
    }

    int answer = 0;
    for (int y = 0; y < board.size(); ++y)
    {
        for (int x = 0; x < board[0].size(); ++x)
        {
            sum[y][x + 1] += sum[y][x];
            if (board[y][x] + sum[y][x] >= 1) ++answer;
        }
    }
    
    return answer;
}