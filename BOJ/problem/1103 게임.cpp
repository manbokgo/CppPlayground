// URL: https://www.acmicpc.net/problem/1103
// Algo: DP, DFS

// 실수가 너무 잦음. 연습 열심히 해야할듯.
// DP 탑다운으로 구현했는데 바텀업은 어떻게? 막다른 길 0 넣는 거부터 시작해서
// 이후 막다른 길로 향하는 타일들을 거슬러가면서 하니깐, 인풋 받을 때
// 어떤 타일을 향할 수 있는 타일들을 저장하는 테이블을 따로 만들어서 해야하나?
// 이론적으로 될 거 같은데 이러면 대부분의 타일의 dp 값을 채우는 거 같아서 비효율적인 듯
// 참고: 아래 링크대로 모든 dp를 다 채우는 것이 비효율적인 경우(ex 백준 1351 무한 수열)에는 탑다운 접근이 맞다함.
// https://devruby7777.tistory.com/entry/Top-down-DP%EC%99%80-Bottom-up-DP%EC%9D%98-%EC%B0%A8%EC%9D%B4%EC%A0%90%EA%B3%BC-%EC%9E%A5%EB%8B%A8%EC%A0%90-%EC%93%B0%EB%8A%94-%EA%B2%BD%EC%9A%B0
// 
// 탑다운처럼 하려면 [1,1] 좌표가 닿을 수 있는 길의 끝에 있는 막다른 길들만 해야하니
// 위상 정렬을 선처리해야하는데 이건 좀 아닌거 같고.

// Start:	240206 18 13
// Read:	18 14
// Think:	18 14
// Code:	19 05
// Total:	0 50

#include <variant>
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


// [y][x]
int tile[50][50];
int dp[50][50];
bool visited[50][50]; // 실수: 이름 그냥 visit로 했는데 std::visit 가 있어서 ambiguous 컴파일 에러 뜸

int N, M;
int dy[4] = {-1, 1, 0, 0};
int dx[4] = {0, 0, -1, 1};

int DFS(int y, int x)
{
    // 실수: 세로가 N이다..
    // 실수: 막다른 길이더라도 횟수에 +1 해야하니 0 리턴. -1로 잘못 잡음.
    // 실수: 타일 횟수가 0이면 여기서 바로 리턴해야함. 안 하면 사이클로 오검출됨. 
    if (y < 0 || x < 0 || y >= N || x >= M || tile[y][x] == 0) return 0;
    if (visited[y][x]) // 이미 밟았던 타일을 또 방문해서 사이클을 돈다? 무한번 가능
    {
        cout << "-1";
        exit(0);
    }
    if (dp[y][x] != -1) return dp[y][x];

    // 방문 ON/OFF 중요. 빼먹으면 안 됨.
    // 예) 아래쪽 루트와 오른쪽 루트 2개가 있을 때
    // 아래쪽 루트 다 돌고 돌아와서 오른쪽 루트 도는데
    // 우연히 아래쪽 루트에서 갔던 타일을 또 밟으면 사이클로 오검출됨.
    visited[y][x] = true;

    dp[y][x] = 0; // 만약 밑의 루프가 다 실패하면 그냥 0임

    // 위, 아래, 좌, 우
    for (int i = 0; i < 4; ++i)
    {
        int ny = y + tile[y][x] * dy[i];
        int nx = x + tile[y][x] * dx[i];

        dp[y][x] = max(dp[y][x], DFS(ny, nx) + 1);
    }

    visited[y][x] = false;

    return dp[y][x];
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N >> M;
    memset(dp, -1, sizeof(dp));

    for (int i = 0; i < N; ++i)
    {
        string s;
        cin >> s;

        for (int j = 0; j < M; ++j)
        {
            if (s[j] == 'H') tile[i][j] = 0;
            else tile[i][j] = s[j] - '0';
        }
    }

    cout << DFS(0, 0);
}
