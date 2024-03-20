// URL: https://www.acmicpc.net/problem/2616
// Algo: DP, 누적 합

// Start:	240320 19 04
// Read:	0 1
// Think:	2 0
// Code:	0 40
// Total:	2 40
// 오모시로이

// 거의 3시간 머리 박아서 끝끝내 승리했다! 아이디어 못 떠오르면 DP 어렵다는 말을 처음 실감한 듯.
// 나이브하게 초안 짠거 시간초과 난거 보고 '음~ DP가 있어야겠는걸~' 싶긴 했지만 어떻게 DP를 넣어야 하는지 감이 전혀 안 왔음.
// 그림판 놓고 끄적이고, 누워서 뇌내 시뮬레이션 돌리고... 1시간 30분 동안 삽질함

// 완전 탐색 방식에서는 DP를 넣으려고 해도 int[50000][50000]로 그냥 무조건 메모리 터지니깐 다른 방식으로 접근함.

// 중간에 len 길이의 열차 한 대 mid를 두고, 그 열차 기준으로 좌우 '구간의 최대값'을 구하는 것을
// mid를 처음부터 끝까지 쭉 순회하는 식으로 풀이해봄. 인덱스 구하는게 아주아주 복잡함.
// 일단 시간 초과는 나지 않고, 직접 만든 테스트케이스에서는 답 잘 나오는데 제출해보니 틀렸습니다 뜸.

// 이 정도로 복잡하게 풀어야하는 문제는 아닌 거 같아서 생각 비우고, 순수하게 DP 바텀업으로 생각해봄.
// '어떤 구간의 최대값'이 중요한 키워드라는걸 깨닫고 30분 생각해서 DP 점화식을 알아냄. 끼얏호우~

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

int dp[4][50'001];
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<int> sum(n + 1);
    for (int i = 1; i <= n; ++i)
    {
        int num;
        cin >> num;
        sum[i] = sum[i - 1] + num;
    }

    int len;
    cin >> len;

    for (int i = 1; i <= 3; ++i)
    {
        for (int j = i * len; j <= n; ++j)
        {
            int tmp = sum[j] - sum[j-len];
            dp[i][j] = max(dp[i][j - 1], tmp + dp[i - 1][j - len]);
        }
    }

    cout << dp[3][n];
}


// 끔찍한 혼종. mid 열차 처음부터 끝까지 옮기면서 좌우 구간 최대값 구하기
/*
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    // n = 50'000;

    vector<int> org(n + 1);
    for (int i = 1; i <= n; ++i)
    {
        int num;
        cin >> num;
        // num = 100;

        org[i] = org[i - 1] + num;
        // org[i] = org[i - 1] + i;
    }

    int len;
    cin >> len;
    // len = 2;
    // len = 500;

    vector<int> sum(n + 1);
    for (int i = 1; i <= n - len + 1; ++i)
    {
        sum[i] = org[i + len - 1] - org[i - 1];
    }

    int maxL = 0;
    int maxR = max(sum.begin() + 1 + 2 * len, sum.end() - len + 1) - sum.begin() - 1;

    int answer = 0;
    for (int i = 1 + len; i <= n - 2 * len + 1; ++i)
    {
        if (sum[maxL] < sum[i - len]) maxL = i - len;
        if (i + len - 1 >= maxR) maxR = max(sum.begin() + i + len, sum.end() - len + 1) - sum.begin() - 1;
        answer = max(answer, sum[i] + sum[maxL] + sum[maxR]);
    }

    cout << answer;
}
*/