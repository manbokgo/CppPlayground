// URL: https://www.acmicpc.net/problem/13558
// Algo: DP (숫자 개수 카운팅, 정해 아님)

// Start:	240324 16 40
// Read:	0 0
// Think:	0 50
// Code:	0 21
// Total:	1 11

// 정해는 고속 푸리에 변환(FFT)를 활용하여 n을 √n 사이즈의 버킷으로 나누고
// 좌우 버킷의 카운팅 배열을 FFT로 빠르게 곱하는... O(√nk log k + n√n) 시간 복잡도로 원래는 다이아급 문제
// https://gratus-blog.tistory.com/94

// 하지만 컴퓨터 성능이 워낙 좋아져서 아래 코드처럼
// 나이브하게 접근하는 O(nk) 풀이로도 풀린다. 그래서 난이도가 골드3으로 낮아졌다고 함.

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
