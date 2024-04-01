// URL: https://school.programmers.co.kr/learn/courses/30/lessons/72413
// Algo: 플로이드

// Start:	240401 22 57
// Read:	0 1
// Think:	0 1
// Code:	0 6
// Total:	0 8

#include <bits/stdc++.h>
using namespace std;

constexpr int INF = 0x3f3f3f3f;

int solution(int n, int s, int a, int b, vector<vector<int>> fares) {
    vector<vector<int>> nodes(n + 1, vector<int>(n + 1, INF));
    for (const auto& fare : fares)
    {
        int c = fare[0];
        int d = fare[1];
        int f = fare[2];
        
        nodes[c][d] = f;
        nodes[d][c] = f;
    }
    
    for (int k = 1; k <= n; ++k)
    {
        nodes[k][k] = 0;
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= n; ++j)
                nodes[i][j] = min(nodes[i][j], nodes[i][k] + nodes[k][j]);
    }
    
    int answer = INF;
    for(int i = 1; i <= n; ++i)
    {
        if (nodes[s][i] == INF ||
           nodes[i][a] == INF ||
           nodes[i][b] == INF) continue;
        
        answer = min(answer, nodes[s][i] + nodes[i][a] + nodes[i][b]);
    }
    
    
    return answer;
}