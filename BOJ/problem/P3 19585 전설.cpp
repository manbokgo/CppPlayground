// URL: https://www.acmicpc.net/problem/19585
// Algo: 트라이 클래스, 해시

// Start:	241218 07 54
// Read:	0 2
// Think:	0 8
// Code:	0 16
// Total:   0 26	

// 시간 제한이 3초이지만 2,000글자 x 20,000팀 = 4천만으로 연산량이 크다.
// 그런데 메모리는 1GB로 넉넉하게 준다. 메모리를 사용하는 알고리즘을 쓴다!

// 메모리는 퍼먹지만 이론적 시간 복잡도 O(|S|)가 좋은 트라이를 사용한다.
// 색깔을 트라이로 만든 후, 팀 이름을 Find하여 색깔이 끝나는 인덱스들을 찾고
// 그 후의 문자열이 닉네임인지 검사한다. 443MB 1040ms

// 알고보니 시간 제한에 아슬아슬하게 해시로만 풀 수 있다. 10MB 2828ms.
// substr을 남발하지 않고 pop_back으로 하기 위해 문자열을 뒤집어서 활용하는 게 핵심이다.
// 색깔과 뒤집은 닉네임을 해시에 넣고, 팀을 뒤집은 후 맨끝부터(실제 문자열의 앞쪽) 쪼개어
// 쪼갠 곳 기준으로 유효한 색깔인지, 남은 문자열이 유효한 닉네임인지를 검사한다.

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) x.begin(), x.end()
#define pb push_back


// 트라이 풀이. 443MB 1040ms
class Trie
{
    bool m_Chk = false;
    map<char, Trie> m_Map;

public:
    void Insert(const string& s)
    {
        auto cur = this;
        for (const char c : s)
            cur = &(cur->m_Map[c]);

        cur->m_Chk = true;
    }

    vector<int> Find(const string& s)
    {
        vector<int> ret;

        auto cur = this;
        for (int i = 0; i < s.size(); ++i)
        {
            const char c = s[i];
            if (!cur->m_Map.count(c)) break;
            cur = &(cur->m_Map[c]);

            if (cur->m_Chk) ret.pb(i);
        }
        return ret;
    }
};

int main()
{
    fastio;

    int c, n;
    cin >> c >> n;

    Trie root;
    unordered_set<string> nicks;

    string tmp;
    while (c--)
    {
        cin >> tmp;
        root.Insert(tmp);
    }

    while (n--)
    {
        cin >> tmp;
        nicks.insert(tmp);
    }

    int T;
    cin >> T;

    while (T--)
    {
        cin >> tmp;
        vector<int> colorEndIndices = root.Find(tmp);

        bool success = false;
        for (const int idx : colorEndIndices)
        {
            if (nicks.count(tmp.substr(idx + 1)))
            {
                success = true;
                break;
            }
        }
        cout << (success ? "Yes" : "No") << '\n';
    }
}

// 시간 아슬아슬한 날먹 풀이. 10MB 2828ms
/*
int main()
{
    fastio;

    int c, n;
    cin >> c >> n;

    unordered_set<string> colors;
    unordered_set<string> nicks;

    string tmp;
    while (c--)
    {
        cin >> tmp;
        colors.insert(tmp);
    }

    while (n--)
    {
        cin >> tmp;
        reverse(all(tmp));
        nicks.insert(tmp);
    }

    int T;
    cin >> T;

    while (T--)
    {
        cin >> tmp;
        reverse(all(tmp));

        string color;
        bool success = false;

        while (!tmp.empty() && color.size() <= 1000)
        {
            color += tmp.back();
            tmp.pop_back();

            if (colors.count(color) && nicks.count(tmp))
            {
                success = true;
                break;
            }
        }
        cout << (success ? "Yes" : "No") << '\n';
    }
}
*/
