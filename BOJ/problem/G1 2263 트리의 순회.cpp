// URL: https://www.acmicpc.net/problem/2263
// Algo: 분할 정복, 트리

// Start:	240604 07 36
// Read:	0 1
// Think:	0 8
// Code:	0 12
// Total:	0 21

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) x.begin(), x.end()
#define pb push_back

int inPos[100'000];
int inOrder[100'000];
int postOrder[100'000];

void Solve(int inSt, int inEn, int poSt, int poEn)
{
    if (inSt > inEn || poSt > poEn) return;

    const int root = postOrder[poEn];
    cout << root << ' ';

    const int rootIdx = inPos[root];
    const int left = poSt + (rootIdx - inSt);
    Solve(inSt, rootIdx - 1, poSt, left - 1); // 왼쪽 트리
    Solve(rootIdx + 1, inEn, left, poEn - 1); // 오른쪽 트리
}

int main()
{
    fastio;
    int n;
    cin >> n;

    for (int i = 0; i < n; ++i)
    {
        cin >> inOrder[i];
        inPos[inOrder[i]] = i;
    }

    for (int i = 0; i < n; ++i)
    {
        cin >> postOrder[i];
    }

    Solve(0, n-1, 0, n-1);
}
