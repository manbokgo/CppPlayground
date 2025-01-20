// URL: https://www.acmicpc.net/problem/10830
// Algo: 수학, 분할 정복 거듭 제곱(루프)

// Start:	250120 09 32
// Read:	0 2
// Think:	0 2
// Code:	0 9
// Total:	0 13

// P5 12850 본대 산책2에서 이미 했었던 행렬을 분할 정복으로 거듭 제곱하기 문제.
// 이진수로 봤을 때 1이 존재하는 곳이, 그때까지의 거듭제곱 g를 정답에 곱해야 하는 곳이다.
// 예를 들어 D가 11 이라면, (1011)2   g^1 * g^2 * g^8  을 한다는 것.

// L79처럼 루프를 돌리는 대신 보다 비효율적이지만 S1 1629 곱셈 문제처럼 재귀 함수로 구현해도 된다.

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) x.begin(), x.end()
#define pb push_back

using pii = pair<int, int>;
using ll = long long;

constexpr ll MOD = 1000;

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

    ll n, b;
    cin >> n >> b;

    Matrix g(n);
    for (int y = 0; y < n; ++y)
    {
        for (int x = 0; x < n; ++x)
        {
            cin >> g.arr[y][x];
        }
    }

    Matrix answer(n, 1);
    while (b)
    {
        if (b & 1) answer *= g;
        g *= g;
        b >>= 1;
    }

    for (int y = 0; y < n; ++y)
    {
        for (int x = 0; x < n; ++x)
        {
            cout << answer.arr[y][x] << ' ';
        }
        cout << '\n';
    }
}
