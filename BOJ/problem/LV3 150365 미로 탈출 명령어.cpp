// URL: https://school.programmers.co.kr/learn/courses/30/lessons/150365
// Algo: 그리디

// Start:	240403 19 03
// Read:	0 1
// Think:	0 3
// Code:	0 15 실패
// Code:	0 17
// Total:	0 36

// 그리디로 풀었는데 백트래킹 DFS로도 (보다 비효율적이지만) 풀이가 가능하긴 하다.

#include <bits/stdc++.h>
using namespace std;

string solution(int n, int m, int y, int x, int ty, int tx, int k) {
    int yDist = ty-y;
    int xDist = tx-x;
    int margin = k - (abs(yDist) + abs(xDist));
    if (margin < 0 || margin % 2 == 1) return "impossible";
    
    string answer;
    answer.reserve(k);
    
    int cd = 0, cu = 0, cr = 0, cl = 0;
    
    if (yDist > 0) cd += yDist;
    else if (-yDist > 0) cu += -yDist;
    
    if (xDist > 0) cr += xDist;
    else if (-xDist > 0) cl += -xDist;
    
    if (n - (y + cd) > 0)
    {
        int num = min(n - (y + cd), margin / 2);
        cd += num;
        cu += num;
        margin -= num * 2;
    }
    
    if ((x - cl) - 1 > 0)
    {
        int num = min((x - cl) - 1, margin / 2);
        cl += num;
        cr += num;
        margin -= num * 2;
    }
    
    while (cd--) answer += "d";
    while (cl--) answer += "l";
    while (margin)
    {
        margin -= 2;
        answer += "rl";
    }
    while (cr--) answer += "r";
    while (cu--) answer += "u";
    
    return answer;
}




// 실패 코드
/*
string solution(int n, int m, int y, int x, int ty, int tx, int k) {
    --y; --x; --ty; --tx;
    int yDist = ty-y;
    int xDist = tx-x;
    int dist = abs(yDist) + abs(xDist);
    if (k < dist) return "impossible";
    
    int margin = k - dist;
    if (margin % 2 == 1) return "impossible";
    
    string answer;
    answer.reserve(k);
    
    if (yDist > 0)
    {
        for (int i = 0; i < yDist; ++i)
            answer += "d";
        y = ty;
    }

    // 여기서 잘못됨. 가능한 d를 일단 모두 때려넣어야 한다.
    if (-xDist > 0)
    {
        for (int i = 0; i < -xDist; ++i)
            answer += "l";
        x = tx;
    }
    
    if (margin > 0)
    {
        string tmp;
        string tmp2;
        
        for (int i = 0; i < margin; i += 2)
        {
            if (y < n - 1)
            {
                ++y;
                tmp += "d";
                tmp2 += "u";
            }
            else if (x > 0)
            {
                --x;
                tmp += "l";
                tmp2 += "r";
            }
            else if (x < m - 1)
            {
                ++x;
                tmp += "r";
                tmp2 += "l";
            }
            else if (y > 0)
            {
                --x;
                tmp += "u";
                tmp2 += "d";
            }
        }

        reverse(tmp2.begin(), tmp2.end());
        answer += tmp;
        answer += tmp2;
    }
    
    if (xDist > 0)
    {
        for (int i = 0; i < xDist; ++i)
            answer += "r";
        x = tx;
    }
    
    if (-yDist > 0)
    {
        for (int i = 0; i < -yDist; ++i)
            answer += "u";
        y = ty;
    }
    
    return answer;
}
*/