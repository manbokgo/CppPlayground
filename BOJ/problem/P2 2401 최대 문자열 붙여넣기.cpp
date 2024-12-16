// URL: https://www.acmicpc.net/problem/2401
// Algo: KMP, DP

// Start:	241216 08 00
// Read:	0 2
// Think:	0 26
// Code:	0 52
// Total:	1 20

// KMP를 통해 L[pos]에 붙여넣을 수 있는 str들을 미리 찾아 avail에 저장해두고, DP를 돌려서 답을 찾는다.

// 처음엔 vector<int> avail[100'000] 으로 두었는데 메모리 터졌다. 
// 10만*500 = 5천 만개의 요소가 있기 떄문에 요소당 1바이트를 사용해야만 50MB 사용으로 제한에 걸리지 않는다.
// bool avail[100'000][500] 으로 고쳐서 정답. 58.8MB 332ms

// 이런 경우 bitset 사용이 유효하다.
// bitset<100'000> avail[500]; 으로 바꾸니 메모리가 1/3 토막남. 17.7MB 244ms
// (단, 위에서까진 avail[pos][i] 였으나 이젠 avail[i][pos] 순서임을 유의)


#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) x.begin(), x.end()
#define pb push_back

int n;
vector<string> strs;
bitset<100'000> avail[500]; // avail[i][pos]: L[pos]에 str[i]를 붙여넣을 수 있다
int dp[100'001]; // dp[pos]: pos에서부터 붙여넣을 수 있는 최대 길이

vector<int> Failure(const string& s)
{
    vector<int> f(s.size());

    int j = 0;
    for (int i = 1; i < s.size(); i++)
    {
        while (j > 0 && s[i] != s[j])
            j = f[j - 1];
        if (s[i] == s[j])
            f[i] = ++j;
    }
    return f;
}

int Solve(int cur)
{
    if (dp[cur] != -1) return dp[cur];

    dp[cur] = Solve(cur + 1);
    for (int i = 0; i < n; ++i)
    {
        if (!avail[i][cur]) continue;
        const string& str = strs[i];
        dp[cur] = max(dp[cur], Solve(cur + str.size()) + (int)str.size());
    }
    return dp[cur];
}

int main()
{
    fastio;
    memset(dp, -1, sizeof(dp));

    string L;
    cin >> L;
    dp[L.size()] = 0;

    cin >> n;

    strs.resize(n);
    for (auto& str : strs) cin >> str;

    vector<int> fail;
    for (int sIdx = 0; sIdx < strs.size(); sIdx++)
    {
        const auto& str = strs[sIdx];
        const vector<int> fail = Failure(str);

        int j = 0;
        for (int i = 0; i < L.size(); i++)
        {
            while (j > 0 && L[i] != str[j])
                j = fail[j - 1];

            if (L[i] == str[j])
            {
                ++j;
                if (j == str.size())
                {
                    avail[sIdx][i - str.size() + 1] = true;
                    j = fail[j - 1];
                }
            }
        }
    }

    cout << Solve(0);
}
