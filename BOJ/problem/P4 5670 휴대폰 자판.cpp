// URL: https://www.acmicpc.net/problem/5670
// Algo: 트라이 클래스 기본

// Start:	241112 17 30
// Read:	0 2
// Think:	0 4
// Code:	0 22
// Total:	0 28

// 처음엔 바킹독식 nxt 배열 트라이 풀이로 풀었다. memset 실수해서 엄청 헤맴. 110MB 796ms
// 다른 풀이를 보니 일반적으로 하는 Trie 클래스 풀이가 더 효율적이고 깔끔한 거 같아서 다시 풀어봄
// 재귀든, 루프든 42MB 416ms

// 재귀가 기본형에서는 직관적이지만 변형이 까다롭고 성능 오버헤드도 있다.
// 루프를 기본적으로 사용한다.

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) x.begin(), x.end()
#define pb push_back

class Trie
{
    bool m_Chk = false;
    map<char, Trie> m_Map;

public:
    void Insert(const string& s)
    {
        auto cur = this;
        for (const char c : s)
        {
            cur = &(cur->m_Map[c]);
        }
        cur->m_Chk = true;
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

    bool Erase(const string& s)
    {
        auto cur = this;
        for (const char c : s)
        {
            if (!cur->m_Map.count(c)) return false;
            cur = &(cur->m_Map[c]);
        }
        if (!cur->m_Chk) return false;
        cur->m_Chk = false;
        return true;
    }

    int Calc(const string& s)
    {
        Trie* cur = this;
        int cnt = 0;

        for (int i = 0; i < s.size(); ++i)
        {
            if (i == 0 || cur->m_Chk || cur->m_Map.size() > 1) ++cnt;
            cur = &(cur->m_Map[s[i]]);
        }
        return cnt;
    }

    // 재귀
    /*
    void Insert(const string& s, int idx = 0)
    {
        if (idx == s.size())
        {
            m_Chk = true;
            return;
        }

        m_Map[s[idx]].Insert(s, idx + 1);
    }

    int Calc(const string& s, int idx = 0)
    {
        if (idx == s.size()) return 0;

        int ret = 0;
        if (idx == 0 || m_Chk || m_Map.size() > 1)
            ++ret;

        ret += m_Map[s[idx]].Calc(s, idx + 1);
        return ret;
    }
    */
};

int main()
{
    fastio;
    cout.precision(2);

    int n;
    while (cin >> n)
    {
        Trie root;
        vector<string> arr(n);
        for (auto& str : arr)
        {
            cin >> str;
            root.Insert(str);
        }

        int cnt = 0;
        for (const auto& str : arr)
            cnt += root.Calc(str);

        cout << fixed << (double)cnt / n << '\n';
    }
}
