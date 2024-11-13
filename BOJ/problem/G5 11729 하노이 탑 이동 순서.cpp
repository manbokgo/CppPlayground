// URL: https://www.acmicpc.net/problem/11729
// Algo: 재귀

// Start:	241113 09 07
// Read:	0 1
// Think:	0 12
// Code:	0 4
// Total:	0 17

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) x.begin(), x.end()
#define pb push_back

void Hanoi(int n, int from, int by, int to)
{
    if (n == 1)
    {
        cout << from << ' ' << to << '\n';
        return;
    }

    Hanoi(n - 1, from, to, by);
    cout << from << ' ' << to << '\n';
    Hanoi(n - 1, by, from, to);
}

int main()
{
    fastio;

    int n;
    cin >> n;
    cout << (1 << n) - 1 << '\n'; // 2^n - 1
    Hanoi(n, 1, 2, 3);
}
