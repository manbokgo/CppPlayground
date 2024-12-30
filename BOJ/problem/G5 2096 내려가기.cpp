// URL: https://www.acmicpc.net/problem/2096
// Algo: DP, 슬라이딩 윈도우

// Start:	241230 13 03
// Read:	0 2
// Think:	0 5
// Code:	0 5
// Total:   0 12

// 메모리 제한이 4MB이다. 나이브하게 푼다면 입력 배열 30만, DP 배열 30만으로 최소 2.4MB를 추가로 쓰게 될텐데
// C++ iostream 에선 기본적으로 2MB를 먹으니 메모리 제한에 걸린다.

// 입력을 받아 바로바로 계산 및 갱신하라는 의도다.
// 원하는 건 마지막행 DP 값 뿐인만큼, DP로 저장해야하는 데이터는 직전 줄의 최솟값 3개, 최댓값 3개 뿐이다.

// 왜 분류에 슬라이딩 윈도우가 있는 지 잘 모르겠음. 이전줄 현재줄 범위가 이동해서 그런거라면 그렇긴 한데...

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) x.begin(), x.end()
#define pb push_back

int dp[2][3];

int main()
{
    fastio;

    int n;
    cin >> n;

    for (int y = 0; y < n; ++y)
    {
        int a, b, c;
        cin >> a >> b >> c;

        int min0 = dp[0][0];
        int min1 = dp[0][1];
        int min2 = dp[0][2];

        dp[0][0] = a + min(min0, min1);
        dp[0][1] = b + min({min0, min1, min2});
        dp[0][2] = c + min(min1, min2);

        int max0 = dp[1][0];
        int max1 = dp[1][1];
        int max2 = dp[1][2];

        dp[1][0] = a + max(max0, max1);
        dp[1][1] = b + max({max0, max1, max2});
        dp[1][2] = c + max(max1, max2);
    }

    cout << max({dp[1][0], dp[1][1], dp[1][2]}) << ' ' << min({dp[0][0], dp[0][1], dp[0][2]});
}
