// URL: https://www.acmicpc.net/problem/10159
// Algo: 플로이드

// Start:	240514 21 10
// Read:	0 2
// Think:	0 2
// Code:	0 6
// Total:	0 10

// 프로그래머스 LV3 49191 순위 문제랑 거의 똑같다. 날먹...

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
bool arr[101][101];

int main()
{
    fastio;

    int n, m;
    cin >> n >> m;

    while (m--)
    {
        int a, b;
        cin >> a >> b;
        arr[a][b] = true;
    }

    for (int k = 1; k <= n; ++k)
    {
        arr[k][k] = true;
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= n; ++j)
                if (arr[i][k] && arr[k][j]) arr[i][j] = true;
    }

    for (int i = 1; i <= n; ++i)
    {
        int num = 0;
        for (int j = 1; j <= n; ++j)
        {
            if (!arr[i][j] && !arr[j][i]) ++num;
        }
        cout << num << '\n';
    }

}
