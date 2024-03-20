// URL: https://www.acmicpc.net/problem/2960
// Algo: 에라토스테네스의 체

// Start:	240213 00 23
// Read:	0 0
// Think:	0 0
// Code:	0 8
// Total:	0 8

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

constexpr ll  MOD = 1000000007;
constexpr int INF = 0x3f3f3f3f;
constexpr ll  LLINF = 1e18;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;

    vector<int> nums(n+1);
    iota(all(nums), 0);

    int removeCount = 0;

    // 소수도 지워버리라는 문제라서 이상하게 되었는데
    // 소수는 남길시,  i * i <= n 조건이면 됨
    for (int i = 2; i <= n; ++i)
    {
        if (nums[i] == -1) continue;

        // 마찬가지로 소수 남기는 쪽이면 j = i * i 로 시작하면 됨
        // i * k (k<i) 까지는 이미 이전 i 순회에서 지워짐
        for (int j = i; j <= n; j += i)
        {
            if (nums[j] == -1) continue;

            ++removeCount;
            if (removeCount == k)
            {
                cout << j;
                exit(0);
            }

            nums[j] = -1;
        }
    }
}
