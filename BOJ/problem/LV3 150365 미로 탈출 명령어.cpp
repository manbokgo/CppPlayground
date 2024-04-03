// URL: https://school.programmers.co.kr/learn/courses/30/lessons/150365
// Algo: 

// Start:	240403 19 03
// Read:	0 1
// Think:	0 3
// Code:	0 15 실패
// Total:	

#include <bits/stdc++.h>
using namespace std;

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