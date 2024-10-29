// URL: https://www.acmicpc.net/problem/1062
// Algo: 백트래킹, 비트마스킹

// Start:	241029 13 15
// Read:	0 2
// Think:	0 5
// Code:	0 11
// Total:	0 18

// 내가 푼 것처럼 간단하게 bool[26]으로 풀지 않고
// int 타입으로 비트마스킹을 하면 더 빠르다. 124ms -> 16ms

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) x.begin(), x.end()
#define pb push_back

vector<string> words;
bool learned[26];
int answer = 0;

int CharToNum(char c) { return c - 'a'; }

void DFS(int idx, int left)
{
    if (left == 0)
    {
        int cnt = 0;
        for (const auto& str : words)
        {
            bool success = true;
            for (const auto& c : str)
            {
                if (!learned[CharToNum(c)])
                {
                    success = false;
                    break;
                }
            }
            if (success) ++cnt;
        }

        answer = max(answer, cnt);
        return;
    }

    for (int i = idx; i < 26; ++i)
    {
        if (learned[i]) continue;
        learned[i] = true;
        DFS(i, left - 1);
        learned[i] = false;
    }
}

int main()
{
    fastio;

    int n, k;
    cin >> n >> k;

    // a, n, t, i, c
    if (k < 5)
    {
        cout << 0;
        return 0;
    }

    words.reserve(n);
    for (int i = 0; i < n; ++i)
    {
        string str;
        cin >> str;
        words.pb(str.substr(4, str.size() - 8));
    }

    learned[CharToNum('a')] = true;
    learned[CharToNum('n')] = true;
    learned[CharToNum('t')] = true;
    learned[CharToNum('i')] = true;
    learned[CharToNum('c')] = true;
    k -= 5;

    DFS(0, k);
    cout << answer;
}
