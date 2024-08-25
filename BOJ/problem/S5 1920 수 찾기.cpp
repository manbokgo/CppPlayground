// URL: https://www.acmicpc.net/problem/1920
// Algo: 이분 탐색 기본 (binary_search)

// Start:	240825 14 31
// Read:	0 1
// Think:	0 0
// Code:	0 4
// Total:	0 5

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) x.begin(), x.end()
#define pb push_back

int arr[100'001];
int n;

bool BinarySearch(int target)
{
    int st = 0;
    int en = n - 1;
    while (st <= en)
    {
        const int mid = (st + en) / 2;
        if (arr[mid] < target) st = mid + 1;
        else if (target < arr[mid]) en = mid - 1;
        else return true;
    }
    return false; // st > en
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
        cout << BinarySearch(target) << '\n';

        // STL
        // cout << binary_search(arr, arr + n, target) << '\n';
    }
}
