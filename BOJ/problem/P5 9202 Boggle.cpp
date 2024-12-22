// URL: https://www.acmicpc.net/problem/9202
// Algo: 트라이, 백트래킹

// Start:	241222 07 56
// Read:	0 2
// Think:	0 10
// Code:	0 15
// Total:   0 27

// 트라이에 사전 단어를 넣어두고 DFS를 돌린다.
// 트라이 노드가 존재하는 경로로만 진행되도록 가지치기가 가능하다.

// 그런데 시간 제한이 10초로 널널해서 브루트포스도 가능하다.
// 그냥 해시 맵에 사전 단어를 몽땅 때려넣고 무지성 브루트포스를 돌려도 되고
// https://sneakstarberry.github.io/posts/nojam9202/
// 사전 단어마다 DFS를 돌려서 단어 경로로만 진행하는 브루트포스도 가능하다
// https://tunsi-niley.tistory.com/15

// 사전의 단어 수는 30만개. 찾은 단어를 어떻게 중복을 피하면서 세냐에 따라 시간이 많이 차이난다.

// 1. set<string>으로 센다면 55MB 5092ms
// 2. unordered_set<string>으로 센다면 53MB 2888ms
// https://www.acmicpc.net/source/87688043

// 3. Trie 종료 노드의 m_Chk를 인덱스로 바꾸고(사전 단어마다 인덱스를 부여하고)
// bool 배열에서 인덱스를 통해 중복 검사를 하면 43MB 376ms. 역시 배열이 짱이다.

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) x.begin(), x.end()
#define pb push_back

class Trie
{
public:
    int m_Chk = 0;
    map<char, Trie> m_Map;

public:
    void Insert(const string& s, int idx = 1)
    {
        auto cur = this;
        for (const char c : s)
            cur = &(cur->m_Map[c]);
        cur->m_Chk = idx;
    }

    bool Find(const string& s)
    {
        auto cur = this;
        for (const char c : s)
        {
            if (!cur->m_Map.count(c)) return false;
            cur = &(cur->m_Map[c]);
        }
        return cur->m_Chk;
    }
};

int dy[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
int dx[8] = {-1, 0, 1, -1, 1, -1, 0, 1};
int score[9] = {0, 0, 0, 1, 1, 2, 3, 5, 11};

bool visited[4][4];
char board[4][4];

int maxScore;
string longest;
bool found[300'001];
int foundCnt;

Trie root;
string cur;

void DFS(int y, int x, Trie* node)
{
    if (node->m_Chk && !found[node->m_Chk])
    {
        found[node->m_Chk] = true;
        ++foundCnt;
        maxScore += score[cur.size()];
        if (cur.size() > longest.size() ||
            (cur.size() == longest.size() && cur < longest))
            longest = cur;
    }
    if (node->m_Map.empty()) return;

    for (int i = 0; i < 8; ++i)
    {
        const int ny = y + dy[i];
        const int nx = x + dx[i];
        if (ny < 0 || ny >= 4 || nx < 0 || nx >= 4) continue;
        if (visited[ny][nx]) continue;
        if (!node->m_Map.count(board[ny][nx])) continue;

        visited[ny][nx] = true;
        cur.push_back(board[ny][nx]);
        DFS(ny, nx, &(node->m_Map[board[ny][nx]]));
        visited[ny][nx] = false;
        cur.pop_back();
    }
}

int main()
{
    fastio;

    int w;
    cin >> w;

    string tmp;
    for (int i = 1; i <= w; ++i)
    {
        cin >> tmp;
        root.Insert(tmp, i);
    }

    int n;
    cin >> n;

    while (n--)
    {
        memset(visited, false, sizeof(visited));
        maxScore = 0;
        longest.clear();
        memset(found, false, sizeof(found));
        foundCnt = 0;
        cur.clear();

        for (int i = 0; i < 4; ++i)
        {
            for (int j = 0; j < 4; ++j)
            {
                cin >> board[i][j];
            }
        }

        for (int i = 0; i < 4; ++i)
        {
            for (int j = 0; j < 4; ++j)
            {
                if (!root.m_Map.count(board[i][j])) continue;

                visited[i][j] = true;
                cur.push_back(board[i][j]);
                DFS(i, j, &(root.m_Map[board[i][j]]));
                visited[i][j] = false;
                cur.pop_back();
            }
        }
        cout << maxScore << ' ' << longest << ' ' << foundCnt << '\n';
    }
}
