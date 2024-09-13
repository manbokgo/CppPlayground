// URL: https://www.acmicpc.net/problem/2295
// Algo: 이분 탐색 or 해시 맵

// Start:	240825 14 09
// Read:	0 1
// Think:	0 10
// Code:	0 5
// Total:	0 16

// x+y+z=w 에서 x,y,z를 고르는 경우의 수는 n^3으로 시간 초과다.
// 식을 x+y = w-z 로 바꾸어 2 * n^2으로 바꾼다.

// x+y를 n^2에 미리 구하고, n^2가지 경우의 w-z을 돌며
// 대응하는 x+y가 있는지 이분 탐색 혹은 unordered_set 하면 됨

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) x.begin(), x.end()
#define pb push_back

int arr[1000];

int main()
{
    fastio;

    int n;
    cin >> n;
    for (int i = 0; i < n; ++i)
        cin >> arr[i];
    sort(arr, arr + n);

    vector<int> sums;
    for (int x = 0; x < n; ++x)
        for (int y = x; y < n; ++y)
            sums.pb(arr[x] + arr[y]);
    sort(all(sums));

    for (int w = n - 1; w >= 0; --w)
    {
        for (int z = 0; z < n; ++z)
        {
            if (binary_search(all(sums), arr[w] - arr[z]))
            {
                cout << arr[w];
                return 0;
            }
        }
    }
}
