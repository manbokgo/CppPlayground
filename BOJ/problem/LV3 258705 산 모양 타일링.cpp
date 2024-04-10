// URL: https://school.programmers.co.kr/learn/courses/30/lessons/258705
// Algo: DP

// Start:	240411 06 06
// Read:	0 3
// Think:	0 22
// Code:	0 6
// Total:	0 31

// 입출력 예 #2 그림이 깔끔해서 편하게 생각해볼 수 있었음

#include <string>
#include <vector>

using namespace std;

constexpr int MOD = 10007;
int dpNon[100001];
int dpOvl[100001];

int solution(int n, vector<int> tops) {
    dpNon[0] = 2 + tops[0];
    dpOvl[0] = 1;
    
    for (int i = 1; i < n; ++i)
    {
        dpNon[i] = (2+tops[i]) * dpNon[i-1] + (1+tops[i]) * dpOvl[i-1]; // 2or3 non + 1or2 ovl
        dpOvl[i] = dpNon[i-1] + dpOvl[i-1];
        
        dpNon[i] %= MOD;
        dpOvl[i] %= MOD;
    }
    
    return (dpNon[n - 1] + dpOvl[n - 1]) % MOD;
}