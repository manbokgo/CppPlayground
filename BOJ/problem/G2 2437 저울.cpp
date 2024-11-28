// URL: https://www.acmicpc.net/problem/2437
// Algo: 그리디

// Start:	241128 10 28
// Read:	0 1
// Think:	0 24
// Code:	0 2
// Total:   0 27

// 1~k까지 모두 만들 수 있다고 했을 때 k+1 이하인 무게의 추 x를 추가하면
// 이 추를 이용하여 x ~ k+x를 만들 수 있으므로 1~k+x까지 모두 만들 수 있게 된다.
// 만약 k+1 초과인 추를 추가한다면 k+1은 만들 수 없게 되는 빈 칸이 된다.

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) x.begin(), x.end()
#define pb push_back

int main()
{
    fastio;

    int n;
    cin >> n;

    vector<int> arr(n);
    for (int& num : arr) cin >> num;

    sort(all(arr));

    int answer = 1;
    for (const int num : arr)
    {
        if (num > answer) break;
        answer += num;
    }
    cout << answer;
}
