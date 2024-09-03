// URL: https://www.acmicpc.net/problem/16234
// Algo: 시뮬레이션, BFS

// Start:	240902 14 07
// Read:	0 1
// Think:	0 1
// Code:	0 14
// Total:	0 16
// 오모시로이
// https://manbokgo.notion.site/G4-16234-C-21c51f6b1c0b4da19d67f918748a517d

// 정말 나이브하게 짠 처음 코드는 432ms였다.
// 다른 C++ 제출을 보니 100ms 이내이던데 왜 이렇게 오래 걸리나 하고 분석해보니

// 1. queue를 재활용하거나,
// 2. BFS를 시작하는 조건을 최적화했다.

// 1번만 적용한 경우, 2번만 적용한 경우가 섞여있는데 각각 시간이 비슷하게 단축되어서
// 내 코드와 무엇이 차이점인지 한눈에 파악하기 힘들었다...


// 내 코드는 BFS를 시작할 때마다 queue를 새로 만들었기 때문에
// 최악의 경우 50x50=2500개의 사이즈를 가지는 queue를, 최대 2000번 동적 할당 및 해제했기 때문에 느린 것이다.

// queue와 deque는 reserve도 불가능한만큼(allocator를 따로 설정하면 가능하나 코테에서는 너무 번거롭다)
// 이 문제와 같이 매우 자주 사용한다면 재활용이 효과적이라는 교훈을 얻었다.

// 1번을 적용하니 100ms로 줄었다.


// 2번은 여러 방법이 있는데,

// 일단 해당 노드가 최소 하나라도 주변과 연합할 수 있는지 확인하고 BFS를 시작할 수도 있다.
// 코드 중복 때문에 예쁘진 않다.

// 내가 적용한 방법은 '이전 턴에 갱신된 노드들만' BFS를 돌리는 것이다.
// 주변과 아무도 연합이 불가능하다고 평가된 노드를 무작정 다음 턴에 또 확인하는 건 불필요한 일이다.

// 연합하여 인구 수가 갱신된 노드만 변화를 가져오기 때문에
// 갱신된 노드들을 BFS에 넣으면  갱신된 노드+그 주변 연합될 수 있는 노드 까지만 확인하기 때문에
// BFS 횟수를 효과적으로 줄일 수 있다.

// 2번까지 적용하니 4ms로 줄었다. 승리!


#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) x.begin(), x.end()
#define pb push_back

using pii = pair<int, int>;

int n, L, R;
int board[50][50];
bool visited[50][50];

int dy[4] = {0, 1, 0, -1};
int dx[4] = {1, 0, -1, 0}; // 동남서북
inline bool OOB(int y, int x) { return y < 0 || y >= n || x < 0 || x >= n; }

queue<pii> q;
vector<pii> moves;

// 최적화 4ms
int main()
{
    fastio;
    cin >> n >> L >> R;
    moves.reserve(n * n);

    queue<pii> updated;
    for (int y = 0; y < n; ++y)
    {
        for (int x = 0; x < n; ++x)
        {
            cin >> board[y][x];
            updated.push({y, x});
        }
    }

    int answer = -1;
    while (!updated.empty())
    {
        memset(visited, false, sizeof(visited));
        int qsz = updated.size();
        while (qsz--)
        {
            const auto [y, x] = updated.front();
            updated.pop();

            if (visited[y][x]) continue;

            moves.clear();
            visited[y][x] = true;

            q.push({y, x});
            int sum = 0;

            while (!q.empty())
            {
                const auto [cy, cx] = q.front();
                q.pop();
                sum += board[cy][cx];
                moves.pb({cy, cx});

                for (int i = 0; i < 4; ++i)
                {
                    const int ny = cy + dy[i];
                    const int nx = cx + dx[i];
                    if (OOB(ny, nx) || visited[ny][nx]) continue;

                    const int diff = abs(board[ny][nx] - board[cy][cx]);
                    if (L <= diff && diff <= R)
                    {
                        visited[ny][nx] = true;
                        q.push({ny, nx});
                    }
                }
            }

            if (moves.size() > 1)
            {
                const int result = sum / moves.size();
                for (const auto [cy, cx] : moves)
                {
                    board[cy][cx] = result;
                    updated.push({cy, cx});
                }
            }
        }
        ++answer;
    }
    cout << answer;
}

// 최적화 이전 100ms
/*
int main()
{
    fastio;
    cin >> n >> L >> R;
    moves.reserve(n * n);

    for (int y = 0; y < n; ++y)
    {
        for (int x = 0; x < n; ++x)
        {
            cin >> board[y][x];
        }
    }

    int answer = 0;
    while (true)
    {
        memset(visited, false, sizeof(visited));
        bool changed = false;

        for (int y = 0; y < n; ++y)
        {
            for (int x = 0; x < n; ++x)
            {
                if (visited[y][x]) continue;

                moves.clear();
                visited[y][x] = true;

                q.push({y, x});
                int sum = 0;

                while (!q.empty())
                {
                    const auto [cy, cx] = q.front();
                    q.pop();
                    sum += board[cy][cx];
                    moves.pb({cy, cx});

                    for (int i = 0; i < 4; ++i)
                    {
                        const int ny = cy + dy[i];
                        const int nx = cx + dx[i];
                        if (OOB(ny, nx) || visited[ny][nx]) continue;

                        const int diff = abs(board[ny][nx] - board[cy][cx]);
                        if (L <= diff && diff <= R)
                        {
                            visited[ny][nx] = true;
                            q.push({ny, nx});
                        }
                    }
                }

                if (moves.size() > 1)
                {
                    changed = true;
                    const int result = sum / moves.size();
                    for (const auto [cy, cx] : moves)
                        board[cy][cx] = result;
                }
            }
        }

        if (!changed) break;
        ++answer;
    }

    cout << answer;
}
*/
