// URL: https://www.acmicpc.net/problem/2616
// Algo: DP, 누적 합

// Start:	240320 19 04
// Read:	0 1
// Think:	2 0
// Code:	0 40
// Total:	2 40
// 오모시로이

/*
거의 3시간 머리 박아서 풀었다. 아이디어 못 떠오르면 DP 어렵다는 말을 처음 실감한 듯.
나이브하게 초안 짠거 시간초과 난거 보고 '음~ DP가 있어야겠는걸~' 싶긴 했지만 어떻게 DP를 넣어야 하는지 감이 전혀 안 왔음.
그림판 놓고 끄적이고, 누워서 뇌내 시뮬레이션 돌리고... 1시간 30분 동안 삽질함

완전 탐색 방식에서는 DP를 넣으려고 해도 int[50000][50000]로 그냥 무조건 메모리 터지니깐 다른 방식으로 접근함.

len 길이의 열차(mid)를 왼->오로 쭉 순회하면서
그 열차 기준으로 좌우 구간 각각에, len 길이의 열차가 최대로 운송할 수 있는 값을 구해서
왼쪽구간최대값 + mid + 오른쪽구간최대값  의 최대값으로 정답을 구하는 풀이. 인덱스 넣는 게 복잡함.

왼쪽 구간의 최대값: mid가 한 칸씩 움직일 때마다 왼쪽 구간의 오른끝에 열차 배치 가능한 위치가 하나씩 늘어나므로
그 위치에 열차를 둘 때의 운송값이 기존 왼쪽구간 최대값보다 큰 지 체크하고 (따지고 보면 DP 배열 계산하는 방식이다)

오른쪽 구간의 최대값: 무식하게 오른쪽 구간을 O(n) 전체 순회해서 최대값을 찾고, 무효화될 때마다 다시 찾는 식으로 푸니
108ms로 정답. (std::max가 아니라 std::max_element 써야하는데 실수해서 오래 삽질함)
하지만 승객수 내림차순이라는 최악 케이스에서는 O(n^2)이므로 시간초과 나는게 맞는데 채점 테케가 부족한 듯하다.

+
왼쪽 구간의 최대값: dpLeft[i] 1 ~ i 구간에서의 최대값
오른쪽 구간의 최대값: dpRight[i]  i ~ n 구간에서의 최대값

위에서 왼쪽 구간의 최대값을 구하는 방식대로 dpLeft를 미리 저장해두고,
유사한 방식으로 --i 루프를 통해 오른쪽 구간의 최대값 dpRight를 미리 저장해두어 써먹음. 4ms 정답.

+
이 정도로(특히 인덱스 쪽) 복잡하게 풀어야하는 문제는 아닌 거 같아서 생각 비우고 순수하게 DP 바텀업으로 생각해봄.
'어떤 구간의 최대값'이 핵심 키워드라는 걸 눈치채고 30분 생각해서 DP 점화식 깨달음. 4ms 정답. 끼얏호우~
위 방식과 비교해 훨씬 깔끔하다. 다른 사람들 풀이도 다 이거인거 보니 이게 의도된 풀이인 듯.
*/

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

/*
// 순수 DP 바텀업
// dp[i][k]  1~k 구간에 i개의 열차를 놓을 때 최대 운송수
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
*/


// mid 열차 왼->오로 옮기면서 좌우 구간 최대값 구하기
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<int> org(n + 1); // 누적 합
    for (int i = 1; i <= n; ++i)
    {
        int num;
        cin >> num;
        org[i] = org[i - 1] + num;
    }

    int len;
    cin >> len;

    vector<int> sum(n + 1); // i번째부터 len 길이의 운송값
    for (int i = 1; i <= n - len + 1; ++i)
    {
        sum[i] = org[i + len - 1] - org[i - 1];
    }

    vector<int> dpLeft(n + 1); // 1 ~ i 구간에서의 최대값
    for (int i = len; i <= n; ++i)
    {
        dpLeft[i] = max(dpLeft[i - 1], sum[i - len + 1]);
    }

    vector<int> dpRight(n + 2); // i ~ n 구간에서의 최대값
    for (int i = n - len + 1; i >= 1; --i)
    {
        dpRight[i] = max(dpRight[i + 1], sum[i]);
    }

    int answer = 0;
    for (int mid = 1 + len; mid <= n - 2 * len + 1; ++mid)
    {
        answer = max(answer, dpLeft[mid - 1] + sum[mid] + dpRight[mid + len]);
    }
    cout << answer;
}
