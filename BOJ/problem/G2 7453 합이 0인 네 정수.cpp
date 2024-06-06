// URL: https://www.acmicpc.net/problem/7453
// Algo: 밋 인 더 미들, 투 포인터

// Start:	240607 07 50
// Read:	0 1
// Think:	0 2
// Code:	0 7
// Total:	0 10

// G1 1208 부분수열의 합2의 처음 풀이처럼 나이브하게 unordered_map을 사용해서 정답 맞음. 9388ms 681MB
// 좀 느리길래 알고리즘 분류 보고 투 포인터로 다시 풀어봄. 2920ms 252MB
// 진짜 unordered_map이 느리고 메모리 많이 잡아먹는구나 다시 느꼈다

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) x.begin(), x.end()
#define pb push_back

using ll = long long;

// 투 포인터 풀이 2920ms 252MB
int n;
ll A[4'000];
ll B[4'000];
ll C[4'000];
ll D[4'000];
vector<ll> leftSum;
vector<ll> rightSum;

int main()
{
    fastio;
    cin >> n;
    for (int i = 0; i < n; ++i)
    {
        cin >> A[i] >> B[i] >> C[i] >> D[i];
    }

    leftSum.reserve(n * n);
    rightSum.reserve(n * n);
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            leftSum.pb(A[i] + B[j]);
            rightSum.pb(C[i] + D[j]);
        }
    }
    sort(all(leftSum));
    sort(all(rightSum), greater<>());

    ll answer = 0;
    int cLeft = 0;
    int cRight = 0;
    const int sz = leftSum.size();
    while (cLeft < sz && cRight < sz)
    {
        const ll sum = leftSum[cLeft] + rightSum[cRight];
        if (sum == 0)
        {
            const ll left = leftSum[cLeft];
            const ll right = rightSum[cRight];

            ll leftCnt = 1;
            ll rightCnt = 1;
            while (++cLeft < sz && leftSum[cLeft] == left) ++leftCnt;
            while (++cRight < sz && rightSum[cRight] == right) ++rightCnt;

            answer += leftCnt * rightCnt;
        }
        else if (sum < 0) { ++cLeft; }
        else { ++cRight; }
    }

    cout << answer;
}

// unordered_map 풀이 9388ms 681MB
/*
int n;
ll A[4'000];
ll B[4'000];
ll C[4'000];
ll D[4'000];
unordered_map<ll, int> leftSum;

int main()
{
    fastio;
    cin >> n;
    for (int i = 0; i < n; ++i)
    {
        cin >> A[i] >> B[i] >> C[i] >> D[i];
    }

    leftSum.reserve(n * n);
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            ++leftSum[A[i] + B[j]];
        }
    }

    ll answer = 0;
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            const ll sum = C[i] + D[j];
            if (leftSum.count(-sum))
                answer += leftSum[-sum];
        }
    }

    cout << answer;
}
*/
