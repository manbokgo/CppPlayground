// URL: https://www.acmicpc.net/problem/11664
// Algo: 삼분 탐색 기본 (실수), 기하학

// Start:	241211 18 33
// Read:	0 1
// Think:	0 7
// Code:	0 18
// Total:	0 26

// https://blog.naver.com/kks227/221432986308
// 삼분 탐색은 볼록함수에서 극값 혹은 최대/최솟값을 찾을 때 사용할 수 있는 방법으로
// 아래로 볼록한 함수의 최솟값, 위로 볼록한 함수의 최댓값을 구할 때 사용한다.
// 이분 탐색은 함수가 단조 증가/감소할 때만 쓸 수 있지만, 삼분 탐색은 좀 더 넓은 범위의 문제에 적용 가능하다.

// 매 루프마다 범위가 2/3으로 줄어드므로, 원래 구간 크기가 N일 때 대충 O(logN)번의 시행 후 결과에 도달한다.

// 최솟값이 아닌데 평탄한 구간이 존재할 경우 삼분 탐색을 쓸 수가 없다.
// 평탄한 구간에 두 삼분점이 존재하게 되면 어느 쪽에서 구간을 줄여야 할지 알 수 없다.
// 단, 평탄한 구간이 반드시 최솟값이면 풀 수 있다.

// 반드시 극값이 한 개만 존재하면서, 극값이 아닌 좌표에서는 반드시 증가하거나 감소하는(즉, 평탄한 구간이 없는) 함수를
// 유니모달(unimodal)한 함수라고 표현한다. 정확히 말해 삼분 탐색은 유니모달한 함수에서 쓸 수 있다.

// 좀 더 수학적으로는, 아래로 볼록한 함수일 경우 어떤 한 x 좌표 k에서 최솟값을 가짐과 동시에
// x < k에선 반드시 감소하고, x > k에선 반드시 증가하는 함수를 말한다.

// 다만 어떤 문제가 유니모달한지를 알아채는 게 어렵다. 이 문제는 직관적으로 알 수 있는 편.

// 실수 범위의 삼분 탐색은 아래와 같이  hi - lo >= 1e-8  처럼 오차를 감안하여 하나의 값을 찾는다면,
// 정수 범위의 삼분 탐색은  hi - lo >= 3  으로 3개 정도의 후보를 만들고 최솟값을 만드는 게 낫다.
// 1개만 찾으려고 범위를 2개까지 줄이면 무한 루프의 위험이 있기 때문.


#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) x.begin(), x.end()
#define pb push_back

double GetDistSquare(double x1, double y1, double z1, double x2, double y2, double z2)
{
    return (x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1) + (z2 - z1) * (z2 - z1);
}

int main()
{
    fastio;
    cout.precision(7);
    cout << fixed;

    double ax, ay, az, bx, by, bz, cx, cy, cz;
    cin >> ax >> ay >> az >> bx >> by >> bz >> cx >> cy >> cz;

    double lo = 0;
    double hi = 1;

    while (hi - lo >= 1e-7)
    {
        const double mid1 = (lo * 2 + hi) / 3;
        const double mid2 = (lo + hi * 2) / 3;

        const double dist1 = GetDistSquare(cx, cy, cz,
            ax * mid1 + bx * (1 - mid1),
            ay * mid1 + by * (1 - mid1),
            az * mid1 + bz * (1 - mid1));

        const double dist2 = GetDistSquare(cx, cy, cz,
            ax * mid2 + bx * (1 - mid2),
            ay * mid2 + by * (1 - mid2),
            az * mid2 + bz * (1 - mid2));

        if (dist1 > dist2) lo = mid1;
        else hi = mid2;
    }

    cout << sqrt(GetDistSquare(cx, cy, cz,
        ax * lo + bx * (1 - lo),
        ay * lo + by * (1 - lo),
        az * lo + bz * (1 - lo)));
}
