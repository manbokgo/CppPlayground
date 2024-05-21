// URL: https://school.programmers.co.kr/learn/courses/30/lessons/12942
// Algo: DP

// Start:	240413 20 03
// Read:	0 2
// Think:	0 20
// Code:	0 5
// Total:	0 27
// 오모시로이

// "연쇄 행렬 곱셈"이라 불리는 유명한 DP 문제였다

// 브루트포스는 안 될 거라고 짐작하고 넘김. 정확하진 않지만 먼저 곱할 것을 순열로 뽑는다치면 n! 정도라고 추정함.
// 실제 시간복잡도는 조합론에서 많이 등장하는 수인 '카탈랑 수'로 대표 예시 중 'n개의 괄호 쌍을 포함하는 수식 조합'에 해당됨
// (총 n쌍의 X, Y로 구성된 문자열인데, 어떤 경우에서도 X보다 많은 수의 Y가 먼저 나올 수 없는 'Dyck Word'에서 X와 Y를 (, )로 치환한 것과 같기 때문)
// 1/n+1 * 2n C n  = (2n)! / ( n! * (n+1)! )   O(4^n / n^(3/2)) 로 추정이 대충 맞았음.

// 다른 접근으로 시간복잡도를 비슷하게 구해보자면, n개의 행렬을 곱할 수 있는 모든 경우의 수를 Tn이라고 할 때
// A1*(A2*A3*A4*...*An)  Tn-1 경우와 (A1*A2*A3*A4*...)*An  Tn-1 경우가 반드시 존재하므로
// Tn >= 2 * Tn-1 임. 이걸 T2 = 1에 도달할 때까지 반복하면
// Tn >= 2 * Tn-1 >= 2^2 * Tn-2 >= 2^3 * Tn-3 ... >= 2^(n-2) * T2  로  최소 O(2^n)임을 알 수 있음

// 처음엔 그리디로 접근했다가 포기함
// 5 3, 3 10, 10 6 예시에서, 모든 행렬 중에 '열'이 제일 큰 것(3 10 x 10 6)부터 곱한다는 식이었는데
// 만약 1 3, 3 4, 4 100 예시라면

// (1) (AB)C
// 1 3 4 + 1 4 100 = 412
// abc + acd = ac(b+d)

// (2) A(BC)
// 1 3 100 + 3 4 100 = 1500
// abd + bcd = bd(a+c)

// 그리디 알고리즘에 따라 (2)를 택하지만 연산 횟수가 더 많으니 그리디로 풀 수 없음.
// 1/b + 1/d < 1/a + 1/c 면 (1) 방법이 더 낫다.

// 그리디 아닌갑다 싶어서 DP 문제인걸 알고 문제 풀기는 했지만
// 이 접근법이 최적 해와 비교해 평균 0~2% 나쁜 해를 O(n)으로 효율적으로 계산하는 알고리즘의 핵심 아이디어였다
// https://en.wikipedia.org/wiki/Matrix_chain_multiplication#Chin-Hu-Shing_approximate_solution

// 최적의 원칙이 적용되는 경우이기 때문에 (최적 해는 부분 사례의 최적 해를 포함한다) DP로 풀 수 있다.
// i~j까지의 행렬의 최소 연산 수 DP[i][j]는, k번째 행렬을 기준으로 좌우를 분할해버린
// (i*...*k)*(k+1*...*j)    DP[i][k] + DP[k+1][j] + i행*k열*j열 (i<=k<j)의 최솟값이다. i=j이면 연산 수는 0.

// 시간복잡도는 O(n^3).
// 위키백과 링크에 따르면 O(n log n) 알고리즘도 존재하고, 깃헙에 C++ 샘플도 존재하긴 한데... 더 깊게 파진 않음.

// 탑다운으로 구현했는데, 바텀업으로 2차원 배열의 대각선 줄을 차근차근 채워가면서도 구현할 수 있음
// DP에 저장되는 최솟값일 때의 k를 따로 배열로 저장해서, 실제 괄호를 어디에 쳐야하는지도 복구할 수 있음

// https://velog.io/@blacklandbird/Chained-Matrix-Multiplication
// https://9-coding.tistory.com/entry/%EC%95%8C%EA%B3%A0%EB%A6%AC%EC%A6%98-%EC%97%B0%EC%87%84-%ED%96%89%EB%A0%AC-%EA%B3%B1%EC%85%88-Matrix-Chain-Multiplication
// https://rainbow97.tistory.com/entry/%EC%95%8C%EA%B3%A0%EB%A6%AC%EC%A6%98-%EB%B6%84%EC%84%9D-03-1-%EB%8F%99%EC%A0%81%EA%B3%84%ED%9A%8DDynamic-Programming

#include <cstring>
#include <vector>

using namespace std;

constexpr int INF = 0x3f3f3f3f;
int dp[200][200];

int solve(int i, int j, const vector<vector<int>>& mat)
{
    if (dp[i][j] != -1) return dp[i][j];
    
    dp[i][j] = INF;
    for (int k = i; k < j; ++k)
        dp[i][j] = min(dp[i][j], solve(i, k, mat) + solve(k+1, j, mat) + mat[i][0] * mat[k][1] * mat[j][1]);
    
    return dp[i][j];
}

int solution(vector<vector<int>> matrix_sizes) {
    memset(dp, -1, sizeof(dp));
    for (int i = 0; i < 200; ++i)
        dp[i][i] = 0;
    
    return solve(0, matrix_sizes.size()-1, matrix_sizes);
}