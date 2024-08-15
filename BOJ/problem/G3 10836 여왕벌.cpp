// URL: https://www.acmicpc.net/problem/10836
// Algo: 시뮬레이션 (+ 누적 합)

// Start:	240815 09 26
// Read:	0 6
// Think:	0 1
// Code:	0 6
// Total:	0 13

// 무지성으로 바로 구현해서 넣어봤는데 바로 정답임.
//
// 왜 G3일까하고 정답을 찾아보니, 테두리의 성장량이 반드시 오름차순으로 주어지기 때문에
// 성장량이 주어지지 않는 애벌레의 성장량은 해당열의 1번째 행의 성장량이라는 점을 응용하는 문제였다.
// 따라서 테두리 성장량들만 다 더하고 답을 구하면 간단하다.

// 누적 합을 쓰면 아주 빠르다. 812ms -> 224ms

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) x.begin(), x.end()
#define pb push_back

int arr[1400];

int main()
{
    fastio;

    int n, T;
    cin >> n >> T;
    const int sz = 2 * n - 1;

    while (T--)
    {
        int n0, n1, n2;
        cin >> n0 >> n1 >> n2;
        ++arr[n0];
        ++arr[n0 + n1];
    }
    for (int i = 1; i < sz; ++i) arr[i] += arr[i - 1];

    for (int y = n - 1; y >= 0; --y)
    {
        cout << arr[y] + 1 << ' ';
        for (int x = n; x < sz; ++x)
        {
            cout << arr[x] + 1 << ' ';
        }
        cout << '\n';
    }
}
