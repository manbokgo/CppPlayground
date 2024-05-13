// URL: https://www.acmicpc.net/problem/16235
// Algo: 시뮬레이션

// Start:	240513 17 44
// Read:	0 3
// Think:	0 1
// Code:	0 32
// Total:	0 36

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define pb push_back
#define all(x) x.begin(), x.end()

int N, M, K;
int A[11][11];

int tile[11][11];
int add[11][11];
int birth[11][11];
deque<int> trees[11][11];

int dy[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
int dx[8] = {-1, 0, 1, -1, 1, -1, 0, 1};
bool OOB(int y, int x) { return y < 1 || y > N || x < 1 || x > N; }


int main()
{
    fastio;

    cin >> N >> M >> K;

    for (int i = 1; i <= N; ++i)
    {
        for (int j = 1; j <= N; ++j)
        {
            cin >> A[i][j];
            tile[i][j] = 5;
        }
    }

    int answer = M;
    while (M--)
    {
        int y, x, z;
        cin >> y >> x >> z;
        trees[y][x].push_front(z);
    }

    while (K--)
    {
        // 봄
        for (int y = 1; y <= N; ++y)
        {
            for (int x = 1; x <= N; ++x)
            {
                auto& now = trees[y][x];
                int sz = now.size();
                for (int i = 0; i < sz; ++i)
                {
                    int age = now.front();
                    now.pop_front();
                    if (tile[y][x] < age)
                    {
                        add[y][x] += age / 2;
                        --answer;
                        continue;
                    }

                    tile[y][x] -= age;
                    now.push_back(age + 1);

                    if ((age + 1) % 5 == 0)
                    {
                        for (int j = 0; j < 8; ++j)
                        {
                            int ny = y + dy[j];
                            int nx = x + dx[j];
                            if (OOB(ny, nx)) continue;
                            ++birth[ny][nx];
                        }
                    }
                }
            }
        }

        // 여름, 가을, 겨울
        for (int y = 1; y <= N; ++y)
        {
            for (int x = 1; x <= N; ++x)
            {
                tile[y][x] += A[y][x];
                tile[y][x] += add[y][x];
                add[y][x] = 0;

                if (birth[y][x])
                {
                    answer += birth[y][x];
                    for (int i = 0; i < birth[y][x]; ++i)
                        trees[y][x].push_front(1);
                    
                    birth[y][x] = 0;
                }
            }
        }
    }

    cout << answer;
}
