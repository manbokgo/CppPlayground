// URL: https://www.acmicpc.net/problem/1525
// Algo: BFS, 해시

// Start:	240521 01 21
// Read:	0 1
// Think:	0 27
// Code:	0 15
// Total:	0 43

// 1차원 인덱스만 두고 dx +1, -1, +3, -3 으로 동서남북 탐색이 가능하다고 잘못 생각함
// 좌표상 빈칸이 맨오른쪽에 있으면(2열) +1 동쪽 탐색이 불가능하지만 진행된다는 문제 있음
// 똑같이 예전에도 당했던 거 같은데 반성하자...

// 원래대로 2차원 좌표를 기준으로 바꿔서 해결

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define pb push_back
#define all(x) x.begin(), x.end()

int dy[4] = {0, 1, 0, -1};
int dx[4] = {1, 0, -1, 0}; // 동남서북
bool OOB(int y, int x) { return y < 0 || y >= 3 || x < 0 || x >= 3; }

unordered_set<string> umap;
const string ans{"123456780"};

int main()
{
    fastio;

    string st;
    st.reserve(9);
    for (int i = 0; i < 9; ++i)
    {
        char c;
        cin >> c;
        st.push_back(c);
    }

    queue<string> q;
    umap.insert(st);
    q.push(st);

    int cnt = 0;
    while (!q.empty())
    {
        int qsz = q.size();
        while (qsz--)
        {
            string cur = std::move(q.front());
            q.pop();

            if (cur == ans)
            {
                cout << cnt;
                return 0;
            }

            const int pos = cur.find('0');
            const int y = pos / 3;
            const int x = pos % 3;
            for (int i = 0; i < 4; ++i)
            {
                const int ny = y + dy[i];
                const int nx = x + dx[i];
                if (OOB(ny, nx)) continue;

                const int nPos = ny * 3 + nx;
                swap(cur[pos], cur[nPos]);
                if (!umap.count(cur))
                {
                    umap.insert(cur);
                    q.push(cur);
                }
                swap(cur[pos], cur[nPos]);
            }
        }
        ++cnt;
    }

    cout << -1;
}
