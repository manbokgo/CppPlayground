// URL: https://www.acmicpc.net/problem/18870
// Algo: 좌표 압축 기본

// Start:	241027 08 47
// Read:	0 1
// Think:	0 3
// Code:	0 2
// Total:	0 6

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
    for (auto& num : arr) cin >> num;

    vector<int> cArr(arr);
    sort(all(cArr));
    cArr.erase(unique(all(cArr)), cArr.end());

    for (const auto num : arr)
        cout << lower_bound(all(cArr), num) - cArr.begin() << ' ';
}
