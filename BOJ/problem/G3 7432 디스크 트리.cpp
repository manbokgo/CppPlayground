// URL: https://www.acmicpc.net/problem/7432
// Algo: 트라이 클래스

// Start:	241116 05 56
// Read:	0 1
// Think:	0 2
// Code:	0 5
// Total:	0 8

// G3 14725 개미굴과 거의 같다. Split 구현만 추가됨.

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) x.begin(), x.end()
#define pb push_back

vector<string> Split(const string& str, const string& delim)
{
    size_t st = 0, en;
    const size_t delimLen = delim.length();

    vector<string> result;
    while ((en = str.find(delim, st)) != string::npos)
    {
        string token = str.substr(st, en - st);
        st = en + delimLen;
        result.push_back(token);
    }

    if (st != str.size())
        result.push_back(str.substr(st));

    return result;
}

class Trie
{
    bool m_Chk = false;
    map<string, Trie> m_Map;

public:
    void Insert(const vector<string>& arr, int idx = 0)
    {
        if (idx == arr.size())
        {
            m_Chk = true;
            return;
        }

        m_Map[arr[idx]].Insert(arr, idx + 1);
    }

    void Print(int depth = 0) const
    {
        for (const auto& [name, node] : m_Map)
        {
            for (int i = 0; i < depth; ++i)
            {
                cout << " ";
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
        string str;
        cin >> str;

        root.Insert(Split(str, "\\"));
    }

    root.Print();
}
