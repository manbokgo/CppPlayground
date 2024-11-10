// URL: https://www.acmicpc.net/problem/14725
// Algo: 트라이 기본 (클래스)

// Start:	241111 08 20
// Read:	0 2
// Think:	0 7
// Code:	0 7
// Total:	0 16

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) x.begin(), x.end()
#define pb push_back

class Trie
{
    map<string, Trie> m_Map;

public:
    void Insert(const vector<string>& s, int idx)
    {
        if (idx == s.size()) return;
        m_Map[s[idx]].Insert(s, idx + 1);
    }

    void Print(int depth = 0) const
    {
        for (const auto& [name, node] : m_Map)
        {
            for (int i = 0; i < depth; ++i)
            {
                cout << "--";
            }
            cout << name << '\n';
            node.Print(depth + 1);
        }
    }
};

int main()
{
    fastio;

    int n;
    cin >> n;

    Trie root;
    while (n--)
    {
        int k;
        cin >> k;

        vector<string> s(k);
        for (auto& str : s) cin >> str;
        root.Insert(s, 0);
    }
    root.Print();
}
