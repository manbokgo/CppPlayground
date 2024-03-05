// URL: https://www.acmicpc.net/problem/2632
// Algo: 누적합

// Start:	240305 12 28
// Read:	0 0
// Think:	0 4
// Code:	0 16
// Total:	0 20

#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define X first
#define Y second
#define all(x) x.begin(), x.end()
#define sortvec(x) sort(all(x))
#define compress(x) x.erase(unique(all(x)), x.end())
#define findvec(x, value) find(all(x), value) != x.end()

using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;

const ll  MOD = 1000000007;
const int INF = 0x3f3f3f3f;
const ll  LLINF = 1e18;

int target;
int a, b;
int aPizza[1'000];
int bPizza[1'000];
int aCount[1'000'001];
int bCount[1'000'001];

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> target >> a >> b;

    int totalSum = 0;
    for (int i = 0; i < a; ++i)
    {
        cin >> aPizza[i];
        totalSum += aPizza[i];
    }
    ++aCount[totalSum];

    totalSum = 0;
    for (int i = 0; i < b; ++i)
    {
        cin >> bPizza[i];
        totalSum += bPizza[i];
    }
    ++bCount[totalSum];


    for (int i = 0; i < a; ++i)
    {
        int sum = 0;
        for (int j = 0; j < a - 1; ++j)
        {
            sum += aPizza[(i + j) % a];
            ++aCount[sum];
        }
    }

    for (int i = 0; i < b; ++i)
    {
        int sum = 0;
        for (int j = 0; j < b - 1; ++j)
        {
            sum += bPizza[(i + j) % b];
            ++bCount[sum];
        }
    }


    int answer = 0;
    if (target <= 1'000'000)
    {
        answer += aCount[target];
        answer += bCount[target];
        for (int i = 1; i < target; ++i)
        {
            answer += aCount[i] * bCount[target - i];
        }
    }
    else // 테스트 케이스 중에 target이 1,000,001 ~ 2,000,000 인 경우가 없는 듯하다. 이하 코드 없어도 정답 처리되는 듯
    {
        for (int i = target - 1'000'000; i <= 1'000'000; ++i)
        {
            answer += aCount[i] * bCount[target - i];
        }
    }

    cout << answer;
}
