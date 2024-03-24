// URL: https://www.acmicpc.net/problem/13558
// Algo: DP (숫자 개수 카운팅)

// Start:	240324 16 40
// Read:	0 0
// Think:	0 50
// Code:	0 21
// Total:	1 11

#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define Y first
#define X second
#define all(x) x.begin(), x.end()
#define SortVec(x) sort(all(x))
#define CompressVec(x) x.erase(unique(all(x)), x.end())
#define ExistInVec(x, value) find(all(x), value) != x.end()

using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using tiii = tuple<int, int, int>;
using tlll = tuple<ll, ll, ll>;

constexpr int INF = 0x3f3f3f3f;

int dpFront[30'001];
int dpBack[30'001];

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    // n = 100000;

    vector<int> nums(n);
    int maxx = 0;
    int minx = INF;
    for (int i = 0; i < n; ++i)
    {
        int num;
        cin >> num;
        // num = 5;

        nums[i] = num;
        ++dpBack[num];
        if (maxx < num) maxx = num;
        if (minx > num) minx = num;
    }

    ll answer = 0;

    --dpBack[nums[0]];
    for (int j = 1; j < n - 1; ++j)
    {
        --dpBack[nums[j]];
        ++dpFront[nums[j - 1]];

        answer += (ll)dpFront[nums[j]] * dpBack[nums[j]];

        int maxA = min(nums[j] - minx, maxx - nums[j]);
        for (int a = 1; a <= maxA; ++a)
        {
            answer += (ll)dpFront[nums[j] - a] * dpBack[nums[j] + a]
                + (ll)dpFront[nums[j] + a] * dpBack[nums[j] - a];
        }
    }

    cout << answer;
}
