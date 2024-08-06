// URL: https://www.acmicpc.net/problem/1135
// Algo: 트리, DFS, 그리디

// Start:	240807 09 35
// Read:	0 2
// Think:	0 6
// Code:	0 7
// Total:	0 15

// DFS 리턴값을 트리 DP로 저장할 수도 있긴 한데
// 단순히 서브 트리의 총 자식 수만 구하는거지 재탐색은 안 하므로 굳이 안 그래도 됨
// G2 치고는 너무 쉽다

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) x.begin(), x.end()
#define pb push_back

int n;
vector<int> child[50];

int DFS(int cur)
{
    if (child[cur].empty()) return 1;

    vector<int> tmp(child[cur].size());
    for (int i = 0; i < child[cur].size(); ++i)
        tmp[i] = DFS(child[cur][i]);

    sort(all(tmp), greater<>());
    int ret = -1;
    for (int i = 0; i < tmp.size(); ++i)
        ret = max(ret, tmp[i] + i);
    return ret + 1;
}

int main()
{
    fastio;
    cin >> n;

    int discard;
    cin >> discard;

    for (int i = 1; i < n; ++i)
    {
        int parent;
        cin >> parent;
        child[parent].pb(i);
    }

    cout << DFS(0) - 1;
}
