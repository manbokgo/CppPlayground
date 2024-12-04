// URL: https://www.acmicpc.net/problem/1002
// Algo: 기하학 (두 원의 위치 관계)

// Start:	241201 15 24
// Read:	0 1
// Think:	0 10
// Code:	0 5
// Total:	0 16

// https://houseofj.tistory.com/167

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) x.begin(), x.end()
#define pb push_back

int main()
{
    fastio;

    int T;
    cin >> T;

    while (T--)
    {
        int x1, y1, r1, x2, y2, r2;
        cin >> x1 >> y1 >> r1 >> x2 >> y2 >> r2;

        const int distSquare = (x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1);
        const int sub = (r2 - r1) * (r2 - r1);
        const int plu = (r2 + r1) * (r2 + r1);

        if (distSquare == 0 && r1 == r2) cout << -1 << '\n';
        else if (distSquare == sub || distSquare == plu) cout << 1 << '\n';
        else if (sub < distSquare && distSquare < plu) cout << 2 << '\n';
        else cout << 0 << '\n';
    }
}
