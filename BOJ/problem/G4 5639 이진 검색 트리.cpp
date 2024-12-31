// URL: https://www.acmicpc.net/problem/5639
// Algo: 트리

// Start:	241231 15 02
// Read:	0 1
// Think:	0 6
// Code:	0 5
// Total:	0 12

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) x.begin(), x.end()
#define pb push_back

int preOrder[10'000];

void PostOrder(int st, int en)
{
    if (st > en) return;
    const int root = preOrder[st];
    int pivot = st + 1;
    while (pivot <= en && root > preOrder[pivot])
        ++pivot;

    PostOrder(st + 1, pivot - 1);
    PostOrder(pivot, en);
    cout << root << '\n';
}

int main()
{
    fastio;

    int num;
    int n = 0;
    while (cin >> num)
        preOrder[n++] = num;

    PostOrder(0, n - 1);
}
