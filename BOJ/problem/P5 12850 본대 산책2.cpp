// URL: https://www.acmicpc.net/problem/12850
// Algo: 인접 행렬 거듭 제곱, 분할 정복(거듭제곱)

// Start:	241004 14 33
// Read:	0 1
// Think:	0 56
// Code:	0 34
// Total:	1 31
// 오모시로이

// 좀 막막해서 일단 S1 12849 본대 산책부터 보았는데 다 동일하나 D가 더 작은 차이가 있는 문제였다.
// 이 문제는 고민하다보니 DP 해결법이 떠올라서 풀었는데 역시나 이 문제에서는 시간 초과다.
//
// https://xy-plane.tistory.com/14
// 결국 패배를 인정하고 풀이법을 찾아봤는데, 언젠가 한 번 봤던 '인접 행렬 거듭제곱'을 이용한 문제였다. 크아아악
// 예컨데 g^2[i][j] 는 간선 2번을 거쳐서 i에서 j로 향하는 경우의 수  를 의미한다. 즉 g^d[0][0] 이 답이 된다.

// 다만 무식하게 처음의 인접 행렬을 d번 곱하는 건 시간이 안 되고, 분할 정복 방식에 따라
// 2의 승수만큼 거듭제곱한 g를 정답에 곱하는 방식을 쓴다.

// 이진수로 봤을 때 1이 존재하는 곳이, 그때까지의 거듭제곱 g를 정답에 곱해야 하는 곳이다.
// 예를 들어 D가 11 이라면, (1011)2   g^1 * g^2 * g^8  을 한다는 것.
// L98 참고. 이건 기억해두면 좋을 것 같다.

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) x.begin(), x.end()
#define pb push_back

using pii = pair<int, int>;
using ll = long long;

constexpr ll MOD = 1000000007;

struct Matrix
{
    int n;
    vector<vector<ll>> arr;

    explicit Matrix(int n, int t = 0)
        : n(n)
    {
        arr.resize(n, vector<ll>(n));
        for (int i = 0; i < n; ++i)
            arr[i][i] = t;
    }

    Matrix operator*(const Matrix& r) const
    {
        Matrix ret(n);
        for (int y = 0; y < n; ++y)
        {
            for (int x = 0; x < n; ++x)
            {
                for (int k = 0; k < n; ++k)
                {
                    ret.arr[y][x] += (arr[y][k] * r.arr[k][x]) % MOD;
                }
                ret.arr[y][x] %= MOD;
            }
        }
        return ret;
    }

    Matrix& operator*=(const Matrix& r)
    {
        (*this) = (*this) * r;
        return *this;
    }
};

int main()
{
    fastio;

    Matrix g(8);
    for (auto [a, b] : {
             pii{0, 1},
             pii{0, 2},
             pii{1, 2},
             pii{1, 3},
             pii{2, 3},
             pii{2, 4},
             pii{3, 4},
             pii{3, 5},
             pii{4, 5},
             pii{4, 6},
             pii{5, 7},
             pii{6, 7}
         })
    {
        g.arr[a][b] = 1;
        g.arr[b][a] = 1;
    }

    int D;
    cin >> D;

    Matrix answer(8, 1);
    while (D)
    {
        if (D & 1) answer *= g;
        g *= g;
        D >>= 1;
    }
    cout << answer.arr[0][0];
}
