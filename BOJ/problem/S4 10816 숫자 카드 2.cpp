// URL: https://www.acmicpc.net/problem/10816
// Algo: 이분 탐색 기본 (lower_bound, upper_bound)

// Start:	240825 15 16
// Read:	0 1
// Think:	0 0
// Code:	0 4
// Total:	0 5

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) x.begin(), x.end()
#define pb push_back

int arr[500'001];
int n;

int LowerBound(int st, int en, int target)
{
    while (st < en)
    {
        const int mid = (st + en) / 2;
        if (target <= arr[mid]) en = mid;
        else st = mid + 1;
    }
    return st;
}

int UpperBound(int st, int en, int target)
{
    while (st < en)
    {
        const int mid = (st + en) / 2;
        if (target < arr[mid]) en = mid;
        else st = mid + 1;
    }
    return st;
}


int main()
{
    fastio;

    cin >> n;
    for (int i = 0; i < n; ++i)
        cin >> arr[i];
    sort(arr, arr + n);

    int T;
    cin >> T;
    while (T--)
    {
        int target;
        cin >> target;
        cout << UpperBound(0, n, target) - LowerBound(0, n, target) << '\n';

        // STL
        // cout << upper_bound(arr, arr + n, target) - lower_bound(arr, arr + n, target) << '\n';
    }
}
