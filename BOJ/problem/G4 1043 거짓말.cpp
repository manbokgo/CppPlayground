// URL: https://www.acmicpc.net/problem/1043
// Algo: 분리 집합

// Start:	250101 16 16
// Read:	0 2
// Think:	0 3
// Code:	0 6
// Total:	0 11

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) x.begin(), x.end()
#define pb push_back

int p[51];
vector<int> parties[51];

int Find(int a)
{
    if (p[a] < 0) return a;
    return p[a] = Find(p[a]);
}

bool Union(int a, int b)
{
    int ap = Find(a);
    int bp = Find(b);

    if (ap == bp) return false;
    // if (-p[ap] < -p[bp]) swap(ap, bp);
    if (ap > bp) swap(ap, bp); // ap가 더 작은 값이 되도록 변형

    p[ap] += p[bp];
    p[bp] = ap;
    return true;
}

int main()
{
    fastio;
    memset(p, -1, sizeof(p));

    int n, m;
    cin >> n >> m;

    int known;
    cin >> known;
    for (int i = 0; i < known; ++i)
    {
        int num;
        cin >> num;
        Union(0, num); // 0이 부모라면 진실을 아는 사람
    }

    for (int i = 1; i <= m; ++i)
    {
        int num;
        cin >> num;
        for (int j = 0; j < num; ++j)
        {
            int cur;
            cin >> cur;
            parties[i].pb(cur);
        }
    }

    for (int i = 1; i <= m; ++i)
    {
        for (int j = 1; j < parties[i].size(); ++j)
        {
            Union(parties[i][j - 1], parties[i][j]);
        }
    }

    int answer = m;
    for (int i = 1; i <= m; ++i)
    {
        for (int j = 0; j < parties[i].size(); ++j)
        {
            if (Find(parties[i][j]) == 0)
            {
                --answer;
                break;
            }
        }
    }

    cout << answer;
}
