// URL: https://www.acmicpc.net/problem/16971
// Algo: 그리디, 누적 합

// Start:	240623 18 18
// Read:	0 2
// Think:	0 5
// Code:	0 59
// Total:	1 6

// 각 요소가 더해지는 횟수:
// 1 2 2 1
// 2 4 4 2
// 1 2 2 1

// 위 횟수에 따라 행과 열의 합(1 2 2 1)을 각각 누적합으로 저장했을 때
// 행 누적합을 양끝에서는 1번, 가운데선 2번씩 더한 게 최종 정답이다
// 따라서 가장 작은 누적합이 양끝에 가도록 행과 열에서 각각 비교해보면 됨

// 이미 행 양끝이 모든 행 누적합 중 가장 작은 첫째, 둘째라면 바꾸면 안 된다.
// 양끝의 누적합 최대값 < 가운데 누적합 최소값  이여야지 진행하도록 함

// 실수: min_element에서 first와 last가 같으면 last를 그냥 리턴시켜버리는 것 때문에 이상한 결과 나옴
// 63줄과 같이 if (n>2)와 같은 조건이 만족할 때 돌려야 함

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) x.begin(), x.end()
#define pb push_back

int n, m;
int weightR[1000];
int weightC[1000];

int main()
{
    fastio;
    cin >> n >> m;
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < m; ++j)
        {
            int num;
            cin >> num;

            if (j == 0 || j == m - 1) weightR[i] += num;
            else weightR[i] += num * 2;

            if (i == 0 || i == n - 1) weightC[j] += num;
            else weightC[j] += num * 2;
        }
    }

    int sum = 0;
    for (int i = 0; i < n; ++i)
    {
        if (i == 0 || i == n - 1) sum += weightR[i];
        else sum += weightR[i] * 2;
    }

    int answer1 = sum;
    if (n > 2)
    {
        const int mnR = *min_element(weightR + 1, weightR + (n - 1));
        const int mxR = max(weightR[0], weightR[n - 1]);
        if (mnR < mxR)
        {
            answer1 -= mnR;
            answer1 += mxR;
        }
    }


    int answer2 = sum;
    if (m > 2)
    {
        const int mnC = *min_element(weightC + 1, weightC + (m - 1));
        const int mxC = max(weightC[0], weightC[m - 1]);
        if (mnC < mxC)
        {
            answer2 -= mnC;
            answer2 += mxC;
        }
    }

    cout << max(answer1, answer2);
}
