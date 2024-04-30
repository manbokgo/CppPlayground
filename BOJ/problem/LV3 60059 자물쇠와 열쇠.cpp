// URL: https://school.programmers.co.kr/learn/courses/30/lessons/60059
// Algo: 시뮬레이션

// Start:	240501 02 15
// Read:	0 1
// Think:	0 3
// Code:	0 19
// Total:	0 23

#include <algorithm>
#include <vector>

using namespace std;
using pii = pair<int, int>;
constexpr int INF = 0x3f3f3f3f;

bool solution(vector<vector<int>> key, vector<vector<int>> lock)
{
    const int M = key.size();
    const int N = lock.size();

    vector<pii> K;
    for (int i = 0; i < M; ++i)
        for (int j = 0; j < M; ++j)
            if (key[i][j]) K.push_back({i, j});

    int count = 0;
    pii hole{};
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            if (!lock[i][j]) {++count; hole = {i, j};}

    for (int rotate = 0; rotate < 4; ++rotate)
    {
        if (rotate != 0)
        {
            for (auto& [y, x] : K)
            {
                swap(y, x);
                x = M - 1 - x;
            }
        }

        for (const auto [hy, hx] : K)
        {
            int dy = hole.first - hy;
            int dx = hole.second - hx;
            int now = count;
            for (const auto [y, x] : K)
            {
                int ny = y + dy;
                int nx = x + dx;
                if (ny < 0 || ny >= N || nx < 0 || nx >= N) continue;
                if (lock[ny][nx]) break;
                --now;
            }
            if (now == 0) return true;
        }
    }

    return false;
}
